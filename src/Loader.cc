

#include "Loader.hh"
#include "Exception.hh"
#include "SaveEntity.hh"
#include "SaveComponent.hh"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zlib.h>

#include <memory>

#ifdef __FreeBSD__
#include <sys/endian.h>
#endif

#define CHUNK_MAGIC ((int64_t)0x9e2a83c1)

Loader::Loader(const std::string &_file): c_filename(_file) {

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

void Loader::parse() {
  // first check the header
  Reader headers(c_save, c_savesize);

  headers
    .fetch(c_header_version)
    .fetch(c_save_version)
    .fetch(c_build_version)
    .fetch(c_world_type)
    .fetch(c_world_properties)
    .fetch(c_session_name)
    .fetch(c_playtime)
    .fetch(c_save_date)
    .fetch(c_visiblity)
    .fetch(c_editor_object_version)
    .fetch(c_mod_metadata)
    .fetch(c_mod_flags);

  printf("Header version: %i\n", c_header_version);
  printf("Save version: %i\n", c_save_version);
  printf("Build version: %i\n", c_build_version);
  printf("World type: %s\n", c_world_type.c_str());
  printf("World properties: %s\n", c_world_properties.c_str());
  printf("Session name: %s\n", c_session_name.c_str());
  printf("Play time: %i seconds\n", c_playtime);
  printf("Save date: %li ticks\n", c_save_date);
  printf("Visibility: %i\n", c_visiblity);
  printf("Editor Object Version: %i\n", c_editor_object_version);
  printf("Mod metadata: %s\n", c_mod_metadata.c_str());
  printf("Mod flags: %i\n", c_mod_flags);

  // chunk
  auto data = ChunkReader(headers);

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
      printf("Objtype: 0x%04x / %i\n", objtype, objtype);
      throw Exception("Unknown object type");
    }
  }

  printf("Loaded %i world objects\n", c_world_object_count);
}


// Reader
Loader::Reader::Reader(): c_buffer(0), c_len(0), c_pos(0) {};
Loader::Reader::Reader(char *_buffer, uint64_t _len): c_buffer(_buffer), c_len(_len), c_pos(0) {
}

Loader::Reader::~Reader() {
}

Loader::Reader& Loader::Reader::debug(uint64_t _lookahead) {
  printf("curr pos: %lu / 0x%lx\n", c_pos, c_pos);
  for (uint64_t i=0; i<_lookahead; ++i ) {
    if ( i ) {
      if ( i%16 == 0 ) printf("\n");
      else if ( i%8 == 0 ) printf(" ");
    }

    printf(" %02x", (uint8_t)(*(c_buffer+c_pos+i)));
  }
  printf("\n");

  return *this;
}

Loader::Reader& Loader::Reader::fetch(int8_t& _val) {
  _val = *((int8_t*)(c_buffer+c_pos));
  ++c_pos;
  return *this;
}

Loader::Reader& Loader::Reader::fetch(int32_t& _val) {
#ifdef __FreeBSD__
  _val = (int32_t)le32toh(*((uint32_t*)(c_buffer+c_pos)));
#endif
  c_pos += 4;
  return *this;
}

Loader::Reader& Loader::Reader::fetch(int64_t& _val) {
#ifdef __FreeBSD__
  _val = (int64_t)le64toh(*((uint64_t*)(c_buffer+c_pos)));
#endif
  c_pos += 8;
  return *this;
}

Loader::Reader& Loader::Reader::fetch(float& _val) {
  if ( sizeof(float) != 4 ) throw Exception("Float size is not 4");
  memcpy((void*)&_val, c_buffer, sizeof(float));
  c_pos += 4;
  return *this;
}

Loader::Reader& Loader::Reader::fetch(Vector2& _val) {
  float x,y;
  fetch(x).fetch(y);
  _val = Vector2(x, y);
  return *this;
}

Loader::Reader& Loader::Reader::fetch(Vector3& _val) {
  float x,y,z;
  fetch(x).fetch(y).fetch(z);
  _val = Vector3(x, y, z);
  return *this;
}

Loader::Reader& Loader::Reader::fetch(Vector4& _val) {
  float x,y,z,w;
  fetch(x).fetch(y).fetch(z).fetch(w);
  _val = Vector4(x, y, z, 2);
  return *this;
}


Loader::Reader& Loader::Reader::fetch(std::string& _val) {
  int32_t len;
  this->fetch(len);

  _val = std::string((const char*)(c_buffer+c_pos), len);
  c_pos += len;
  return *this;
}

char* Loader::Reader::pass(uint64_t _len) {
  uint64_t ppos = c_pos;
  c_pos += _len;
  return c_buffer+ppos;
}

void Loader::Reader::dump(const std::string _file) {
  int fd;

  if ( (fd = open(_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 ) {
    throw Exception("open() failed");
  }

  write(fd, c_buffer, c_len);

  close(fd);
}

Loader::ChunkReader::ChunkReader(Reader &_reader): c_reader(_reader) {
  // we decompress the whole data here

  c_buffer = 0;
  c_len = 0;
  c_pos = 0;

  int ucret;
  z_stream strm;


  int64_t magic, maxchunk, clen1, uclen1, clen2, uclen2;
  while ( !c_reader.eof() ) {
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    if ( inflateInit(&strm) != Z_OK )
      throw Exception("iniflateInit error");
    // fetch the chunk header
    // https://satisfactory.fandom.com/wiki/Save_files#Compressed_Save_File_Format
    c_reader
      .fetch(magic)
      .fetch(maxchunk)
      .fetch(clen1)
      .fetch(uclen1)
      .fetch(clen2)
      .fetch(uclen2)
      ;
    if ( magic != CHUNK_MAGIC ) {
      printf("Expected/got magic: 0x%08lx/0x%08lx\n", CHUNK_MAGIC, magic);
      inflateEnd(&strm);
      throw Exception("Chunk magic byte off");
    }

    /*
    printf("\nMagic: 0x%08lx maxchunk: %li\n", magic, maxchunk);
    printf("Len1 comp/uncomp: %li/%li\n", clen1, uclen1);
    printf("Len2 comp/uncomp: %li/%li\n", clen2, uclen2);
    */
 
    //c_reader.debug(32);
    // set the input
    strm.avail_in = clen1;
    strm.next_in = (Bytef*)c_reader.pass(clen1);
    //printf("next_in[2]: %02x %02x\n", strm.next_in[0], strm.next_in[1]);

    // increase our buffer by this chunk's uncompressed size
    c_len = c_pos + uclen2*2;
    c_buffer = (char*)realloc((void*)c_buffer, c_len);

    do {
      strm.avail_out = c_len - c_pos;
      strm.next_out = (Bytef*)(c_buffer + c_pos);
      if ( (ucret = inflate(&strm, Z_NO_FLUSH)) != Z_OK ) {
	inflateEnd(&strm);
	switch (ucret) {
	case Z_NEED_DICT:
	  throw Exception("Z_NEED_DICT");
	case Z_DATA_ERROR:
	  throw Exception("Z_DATA_ERROR");
	case Z_MEM_ERROR:
	  throw Exception("Z_MEM_ERROR");
	case Z_STREAM_ERROR:
	  throw Exception("Z_STREAM_ERROR");
	}
      }
      c_pos += strm.avail_out;
      //printf("c_pos: %li avail_out: %u\n", c_pos, strm.avail_out);
    } while ( strm.avail_out == 0 );
    
    inflateEnd(&strm);
  }

  printf("Finished loading compressed chunks, bufsize: %li\n", c_len);
  c_pos = 0;
  // finish inflating
}

Loader::ChunkReader::~ChunkReader() {
  if ( c_buffer ) free(c_buffer);
}
