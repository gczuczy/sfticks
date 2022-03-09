
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <boost/functional/hash.hpp>

#include "Reader.hh"
#include "Exception.hh"

#define CHUNK_MAGIC ((int64_t)0x9e2a83c1)

std::string hexhash(const std::string& _str) {
  boost::hash<std::string> strhash;
  char buff[32];
  int len;

  size_t h = strhash(_str);
  len = snprintf(buff, 31, "%04zx", h);
  return std::string(buff, len);
}

bool Reader::c_in_exception(false);
uint32_t Reader::c_id_idx(0);

Reader::Reader(): c_buffer(0), c_len(0), c_pos(0), c_hasparent(false) {
  c_id = ++c_id_idx;
}

Reader::Reader(Reader& _parent, uint64_t _len, std::string _file, int _line, std::string _comment)
  : c_pos(0), c_file(_file), c_line(_line), c_comment(_comment), c_hasparent(true) {
  c_id = ++c_id_idx;
  c_buffer = _parent.pass(_len);
  c_len = _len;
  c_parent_file = _parent.c_file;
  c_parent_line = _parent.c_line;
  c_parent_comment = _parent.c_comment;
  c_parent_id = _parent.c_id;
#ifdef SFT_DEBUG
  char buff[128];
  int blen = snprintf(buff, 127, "/tmp/reader-%u.dump", c_id);
  dump(std::string(buff, blen));
#endif
}

Reader::Reader(Reader& _parent, const std::string _mark, uint64_t _len, std::string _file, int _line,
	       std::string _comment)
  : c_pos(0), c_file(_file), c_line(_line), c_comment(_comment), c_hasparent(true) {
  c_id = ++c_id_idx;
  c_pos = _parent.offset(_mark);
  c_buffer = _parent.pass(_mark, _len);
  c_len = _len;
  c_parent_file = _parent.c_file;
  c_parent_line = _parent.c_line;
  c_parent_comment = _parent.c_comment;
  c_parent_id = _parent.c_id;
#ifdef SFT_DEBUG
  char buff[128];
  int blen = snprintf(buff, 127, "/tmp/reader-%i.dump", c_id);
  dump(std::string(buff, blen));
#endif
}

Reader::Reader(char *_buffer, uint64_t _len): c_buffer(_buffer), c_len(_len), c_pos(0), c_hasparent(false) {
  c_id = ++c_id_idx;
}

Reader::~Reader() noexcept(false) {
  if ( c_in_exception ) return;
  if ( c_pos < c_len ) {
    printf(" ! Unused content in reader(%u) from %s:%i - %s\n",
	   c_id, c_file.c_str(), c_line, c_comment.c_str());
    printf(" Pos: %li / 0x%lx\n Len: %li / 0x%lx\n",
	   c_pos, c_pos,
	   c_len, c_len);
    if ( c_hasparent )
      printf(" Parent(%u): %s:%i - %s\n",
	     c_id, c_file.c_str(), c_line, c_comment.c_str());

    std::string hash = hexhash(std::string(c_buffer, c_len));
    debug(128, hash);
    dump(std::string("/tmp/")+hash+std::string(".dump"));
    c_in_exception = true;
    throw Exception("Reader has unused content");
  }
}

Reader& Reader::debug(uint64_t _lookahead, std::string _label) {
  if ( _label.length() ) printf("Reader(%u) curr pos: %lu / 0x%lx\t%s\n     len: %lu / 0x%lx\n",
				c_id,
				c_pos, c_pos, _label.c_str(),
				c_len, c_len);
  else printf("Reader(%u) curr pos: %lu / 0x%lx\n     len: %lu / 0x%lx\n",
	      c_id,
	      c_pos, c_pos,
	      c_len, c_len);

  for (uint64_t i=0; i<_lookahead && c_pos+i<c_len; ++i ) {
    if ( i ) {
      if ( i%16 == 0 ) printf("\n");
      else if ( i%8 == 0 ) printf(" ");
    }

    printf(" %02x", (uint8_t)(*(c_buffer+c_pos+i)));
  }
  printf("\n");

  // marks
  if ( !c_marks.empty() ) {
    printf(" Markings:\n");
    for (auto it = c_marks.begin(); it != c_marks.end(); ++it)
      printf("  - %s: %lu\n", it->first.c_str(), it->second);
  }

  return *this;
}

void Reader::lencheck(int64_t _l) {
  if ( c_pos + _l > c_len ) {
    char buff[128];
    int len;
    len = snprintf(buff, 128, "Reader(%u)::lencheck pos(%li) + l(%li) > len(%li)",
		   c_id, c_pos, _l, c_len);
    std::string msg(buff, len);
    debug(32, msg);
    EXCEPTION(msg);
  }
}

uint64_t Reader::offset(const std::string& _mark) {
  auto it = c_marks.find(_mark);
  if ( it == c_marks.end() ) {
    EXCEPTION("Mark not found");
  }
  return c_pos - it->second;
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
  if ( len > 0 ) {
    _val = std::string((const char*)(c_buffer+c_pos), len-1);
    c_pos += len;
  } else if ( len < 0 ) {
    _val = std::string((const char*)(c_buffer+c_pos), (-2*len)-1);
    c_pos += -2*len;
  } else {
    _val.clear();
  }
  
  return *this;
}

char* Reader::pass(uint64_t _len) {
  lencheck(_len);
  uint64_t ppos = c_pos;
  c_pos += _len;
  return c_buffer+ppos;
}

char* Reader::pass(const std::string& _mark, uint64_t _len) {
  auto it = c_marks.find(_mark);
  if ( it == c_marks.end() ) {
    EXCEPTION("No such mark");
  }
  c_pos = it->second;
  return pass(_len);
}

Reader& Reader::dump(const std::string _file) {
  int fd;

  printf("Reader(%u)::dump(%s), %li bytes\n", c_id, _file.c_str(), c_len);
  if ( (fd = open(_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 ) {
    throw Exception("open() failed");
  }

  write(fd, c_buffer, c_len);

  close(fd);
  return *this;
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
