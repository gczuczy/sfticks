

#include "Loader.hh"
#include "Exception.hh"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#ifdef __FreeBSD__
#include <sys/endian.h>
#endif

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
  /*
    int32_t c_header_version;
    int32_t c_save_version;
    int32_t c_build_version;
    std::string c_world_type;
    std::string c_world_properties;
    std::string c_session_name;
    int32_t c_playtime; // seconds
    int64_t c_save_date; //ticks
    int8_t c_visiblity;
    int32_t c_editor_object_version;
    std::string c_mod_metadata;
    int32_t c_mod_flags;
  */
  // first check the header
  Reader headers(c_save, c_savesize);

  c_header_version = headers.fetch_int32(0);
  printf("Header version: %i\n", c_header_version);

  c_save_version = headers.fetch_int32(4);
  printf("Save version: %i\n", c_save_version);

  c_build_version = headers.fetch_int32(8);
  printf("Build version: %i\n", c_build_version);
}

// Reader
Loader::Reader::Reader(char *_buffer, uint64_t _len): c_buffer(_buffer), c_len(_len) {
}

Loader::Reader::~Reader() {
}

int32_t Loader::Reader::fetch_int32(uint64_t _pos) const {
#ifdef __FreeBSD__
  return (int32_t)le32toh(*((uint32_t*)(c_buffer+_pos)));
#endif
}

