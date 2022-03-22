
#include "Loader.hh"
#include "Exception.hh"
#include "Reader.hh"
#include "Trace.hh"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <memory>

#ifdef __FreeBSD__
#include <sys/endian.h>
#endif

Loader::Loader(const std::string &_file): c_filename(_file) {
  TRACE;

  t.printf("Loading save file: %s\n", c_filename.c_str());

  if ( (c_fd = open(c_filename.c_str(), O_RDONLY))<0 )
    throw Exception("Unable to open file");

  // check its size
  struct stat st;
  if ( fstat(c_fd, &st)<0 )
    throw Exception("Unable to stat file");
  c_savesize = st.st_size;
  t.printf("Save size: %lu bytes\n", c_savesize);

  // map it into memory
  if ( (c_save = (char*)mmap(0, // addr, hint
			     c_savesize, //size
			     PROT_READ, // prot
			     MAP_PRIVATE|MAP_PREFAULT_READ, //flags
			     c_fd, //fd
			     0)) == MAP_FAILED) { //size
    t.printf("Map failed: %s\n", strerror(errno));
    throw Exception("mmap failed");
  }
}

Loader::~Loader() {
  close(c_fd);
  munmap(c_save, c_savesize);
}

std::shared_ptr<World> Loader::parse() {
  TRACE;
  std::shared_ptr<World> world;
  Reader headers(c_save, c_savesize);
  World::Header world_header;

  world_header.deserialize(headers);
  world = std::make_shared<World>(world_header);
  
  auto data = ChunkReader(headers);
  try {
    world->deserialize(data);
  }
  catch (Exception& e) {
    printf("World->deserialize exception: %s\n", e.what());
    throw e;
  }

  return world;
  /*
  // first check the header


  // chunk

  //data.dump(std::string("/tmp/sf_")+c_session_name);

  data.skip(4).fetch(c_world_object_count);

  // read world objects
  for (int i=0; i<c_world_object_count; ++i) {
    int32_t objtype, len, index(0);
    std::string name, proptype, blah;

    data.fetch(objtype);
    std::shared_ptr<SaveObject> obj;
    if ( objtype == 1 ) {
      obj = std::make_shared<SaveEntity>(data);
    } else if ( objtype == 0 ) {
      obj = std::make_shared<SaveComponent>(data);
    } else {
      t.printf("Objtype: 0x%04x / %i\n", objtype, objtype);
      throw Exception("Unknown object type");
    }
    c_world.add(obj);
  }
  t.printf("Loaded %i world objects\n", c_world_object_count);
  return;

  // read world ojbect properties
  data.fetch(c_world_object_property_count);
  if ( c_world_object_count != c_world_object_property_count ) {
    t.printf("Object(%i) and property(%i) count doesn't match\n",
	   c_world_object_count,
	   c_world_object_property_count);
    throw Exception("Obj and prop count doesn't match");
  }
  t.printf("World object property count: %i\n", c_world_object_property_count);
  for (int i=0; i<c_world_object_property_count; ++i) {
    int32_t len;
    data(len);
    Reader prop(data, len, __FILE__, __LINE__, "property");

    try {
      c_world[i]->loadProperties(prop);
    }
    catch (Exception &e) {
      t.printf("Loader caught exception, showing reader and dumping: %s\n", e.what());
      prop.debug(128);
      prop.dump("/tmp/prop.except");
      throw e;
    }

    if ( !prop.eof() ) {
      t.printf("\n!!! Haven't read all properties (%lu/%lu)\n", prop.pos(), prop.len());
      prop.dump("/tmp/prop.unread.dump").debug(128, "unread props");
      c_world[i]->debug();
      throw Exception("Prop buffer not empty");
    }
  } // for world object property
  */
}
