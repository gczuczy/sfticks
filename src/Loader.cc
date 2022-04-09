
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

namespace SFT {

  Loader::Loader(const std::string &_file): c_filename(_file) {
    //TRACE;

    printf("Loading save file: %s\n", c_filename.c_str());

    if ( (c_fd = open(c_filename.c_str(), O_RDONLY))<0 )
      throw Exception("Unable to open file");

    // check its size
    struct stat st;
    if ( fstat(c_fd, &st)<0 )
      throw Exception("Unable to stat file");
    c_savesize = st.st_size;
    printf("Save size: %lu bytes\n", c_savesize);

    // map it into memory
    if ( (c_save = (char*)mmap(0, // addr, hint
			       c_savesize, //size
			       PROT_READ, // prot
			       MAP_PRIVATE|MAP_PREFAULT_READ, //flags
			       c_fd, //fd
			       0)) == MAP_FAILED) { //size
      printf("Map failed: %s\n", strerror(errno));
      throw Exception("mmap failed");
    }
  }

  Loader::~Loader() {
    close(c_fd);
    munmap(c_save, c_savesize);
  }

  std::shared_ptr<FG::World> Loader::parse() {
    //TRACE;
    std::shared_ptr<FG::World> world;
    Reader headers(c_save, c_savesize);
    FG::World::Header world_header;

    world_header.deserialize(headers);
    world = std::make_shared<FG::World>(world_header);
  
    auto data = ChunkReader(headers);
    try {
      world->deserialize(data);
    }
    catch (Exception& e) {
      printf("World->deserialize exception: %s\n", e.what());
      throw e;
    }

    return world;
  }

}
