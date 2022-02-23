
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "Reader.hh"
#include "Exception.hh"

#define CHUNK_MAGIC ((int64_t)0x9e2a83c1)

// Reader
Reader::Reader(): c_buffer(0), c_len(0), c_pos(0) {
}

Reader::Reader(Reader& _parent, uint64_t len): c_pos(0) {
  c_buffer = _parent.pass(len);
  c_len = len;
}

Reader::Reader(char *_buffer, uint64_t _len): c_buffer(_buffer), c_len(_len), c_pos(0) {
}

Reader::~Reader() {
}

Reader& Reader::debug(uint64_t _lookahead) {
  printf("curr pos: %lu / 0x%lx\n", c_pos, c_pos);
  for (uint64_t i=0; i<_lookahead && c_pos+i<c_len; ++i ) {
    if ( i ) {
      if ( i%16 == 0 ) printf("\n");
      else if ( i%8 == 0 ) printf(" ");
    }

    printf(" %02x", (uint8_t)(*(c_buffer+c_pos+i)));
  }
  printf("\n");

  return *this;
}

void Reader::lencheck(int64_t _l) {
  if ( c_pos + _l > c_len ) {
    char buff[128];
    int len;
    len = snprintf(buff, 128, "Reader::lencheck pos(%li) + l(%li) > len(%li)\n",
		   c_pos, _l, c_len);
    throw Exception(std::string(buff, len));
  }
}

Reader& Reader::fetch(int8_t& _val) {
  lencheck(1);
  _val = *((int8_t*)(c_buffer+c_pos));
  ++c_pos;
  return *this;
}

Reader& Reader::fetch(int32_t& _val) {
  lencheck(4);
#ifdef __FreeBSD__
  _val = (int32_t)le32toh(*((uint32_t*)(c_buffer+c_pos)));
#endif
  c_pos += 4;
  return *this;
}

Reader& Reader::fetch(int64_t& _val) {
  lencheck(8);
#ifdef __FreeBSD__
  _val = (int64_t)le64toh(*((uint64_t*)(c_buffer+c_pos)));
#endif
  c_pos += 8;
  return *this;
}

Reader& Reader::fetch(float& _val) {
  if ( sizeof(float) != 4 ) throw Exception("Float size is not 4");
  lencheck(4);
  memcpy((void*)&_val, c_buffer, sizeof(float));
  c_pos += 4;
  return *this;
}

Reader& Reader::fetch(Vector2& _val) {
  float x,y;
  fetch(x).fetch(y);
  _val = Vector2(x, y);
  return *this;
}

Reader& Reader::fetch(Vector3& _val) {
  float x,y,z;
  fetch(x).fetch(y).fetch(z);
  _val = Vector3(x, y, z);
  return *this;
}

Reader& Reader::fetch(Vector4& _val) {
  float x,y,z,w;
  fetch(x).fetch(y).fetch(z).fetch(w);
  _val = Vector4(x, y, z, 2);
  return *this;
}


Reader& Reader::fetch(std::string& _val) {
  int32_t len;
  this->fetch(len);

  lencheck(len);
  if ( len ) _val = std::string((const char*)(c_buffer+c_pos), len-1);
  else _val.empty();
  
  c_pos += len;
  return *this;
}

char* Reader::pass(uint64_t _len) {
  lencheck(_len);
  uint64_t ppos = c_pos;
  c_pos += _len;
  return c_buffer+ppos;
}

void Reader::dump(const std::string _file) {
  int fd;

  printf("Reader::dump(%s), %li bytes\n", _file.c_str(), c_len);
  if ( (fd = open(_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 ) {
    throw Exception("open() failed");
  }

  write(fd, c_buffer, c_len);

  close(fd);
}

ChunkReader::ChunkReader(Reader &_reader): c_reader(_reader) {
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

ChunkReader::~ChunkReader() {
  if ( c_buffer ) free(c_buffer);
}
