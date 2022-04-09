
#include <stdio.h>
#include <stdint.h>

#include <iostream>
#include <algorithm>

#include <boost/program_options.hpp>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <zlib.h>

#include "Timer.hh"
#include "Exception.hh"

namespace po = boost::program_options;

static char* load(std::string& _file, uint64_t &_len);
static void compress(char* _data, uint64_t _datalen, int _level, int _zchunksize);
static void compress_chunked(char* _data, uint64_t _datalen, int _level, int _zchunksize, uint64_t _chunksize=128*1024*1024);

int main(int argc, char* argv[]) {
  std::string filename;

  // command line options
  po::options_description desc("SatisFactory save compression tests");
  desc.add_options()
    ("help", "Show the help message")
    ("data-file", po::value<std::string>(&filename)->required(), "Path to the save file")
    ;

  po::positional_options_description p;
  p.add("data-file", -1);

  po::variables_map vm;
  try {
    po::store(po::command_line_parser(argc, argv).
	      options(desc).positional(p).run(), vm);
    if ( vm.count("help") ) {
      std::cout << desc << std::endl;
      return 1;
    }
    po::notify(vm);
  }
  catch (boost::program_options::required_option &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  if ( vm.count("help") ) {
    std::cout << desc << std::endl;
    return 1;
  }

  char *data(0);
  uint64_t datalen;

  try{
    SFT::Timer t("Data loading");
    data = load(filename, datalen);
  }
  catch (SFT::Exception &e) {
    printf("Exception while loading data: %s\n", e.what());
    return 1;
  }

  int zchunksize = 16384;
  int chunksize = 128*1024*1024;
  printf("Zlib chunk size: %i\n", zchunksize);
  printf("Satisfactory chunksize: %i\n", chunksize);

  try {
    {
      SFT::Timer t("Complete compression, level=0");
      compress(data, datalen, 0, zchunksize);
    }
    {
      SFT::Timer t("Complete compression, level=1");
      compress(data, datalen, 1, zchunksize);
    }
    {
      SFT::Timer t("Chunked compression, level=0");
      compress_chunked(data, datalen, 0, zchunksize, chunksize);
    }
    {
      SFT::Timer t("Chunked compression, level=1");
      compress_chunked(data, datalen, 1, zchunksize, chunksize);
    }
  }
  catch (SFT::Exception &e) {
    printf("Exception while compressing data: %s\n", e.what());
    free(data);
    return 1;
  }

  if (data) free(data);
  return 0;
}

void compress(char* _data, uint64_t _datalen, int _level, int _zchunksize) {
  z_stream strm;
  char* buffer;
  int pos(0);
  int ret;
  int flush;
  int bufsize = _zchunksize*8;
  buffer = (char*)malloc(bufsize);

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;

  if ( (ret = deflateInit(&strm, _level))!= Z_OK ) {
    free(buffer);
    throw SFT::Exception("deflateInit failed");
  }

  do {
    strm.avail_in = std::min((int)(pos+_zchunksize), (int)_datalen)-pos;
    flush = pos+_zchunksize >= _datalen ? Z_FINISH : Z_NO_FLUSH;
    strm.next_in = (Bytef*)(_data + pos);

    do {
      strm.avail_out = bufsize;
      strm.next_out = (Bytef*)buffer;

      ret = deflate(&strm, flush);
      if ( ret == Z_STREAM_ERROR ) {
	free(buffer);
	deflateEnd(&strm);
	throw SFT::Exception("Z_STREAM_ERROR");
      }

      
    } while( strm.avail_out == 0);
    
    pos += _zchunksize;
  } while ( flush != Z_FINISH);

  free(buffer);
  deflateEnd(&strm);
}

void compress_chunked(char* _data, uint64_t _datalen, int _level, int _zchunksize, uint64_t _chunksize) {
  int pos(0);
  int stepsize;

  do {
    stepsize = std::min((int)(pos+_chunksize), (int)_datalen) - pos;
    compress(_data+pos,
	     stepsize,
	     _level,
	     _zchunksize);
    pos += stepsize;
  } while ( pos < _datalen);
}


char* load(std::string& _file, uint64_t &_len) {
  int fd;

  if ( (fd = open(_file.c_str(), O_RDONLY)) == -1 )
    throw SFT::Exception("Open error");

  struct stat st;
  if ( fstat(fd, &st)<0 ) {
    close(fd);
    throw SFT::Exception("Unable to stat file");
  }
  _len = st.st_size;
  printf("Data size: %lu bytes\n", _len);

  char *buff = (char*)malloc(_len);
  int r;

  if ( (r=read(fd, (void*)buff, _len))<0 ) {
    close(fd);
    throw SFT::Exception("Read error");
  }
  
  printf("read: %i\n", r);

  close(fd);
  return buff;
}
