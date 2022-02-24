
#ifndef SFT_READERS_H
#define  SFT_READERS_H

#include <stdint.h>

#include <string>

#include "vectors.hh"

class ChunkReader;
class Reader {
protected:
  Reader();
public:
  Reader(const Reader&) = delete;
  Reader(Reader& _parent, uint64_t len);
  Reader(char *_buffer, uint64_t _len);
  virtual ~Reader();

  Reader& debug(uint64_t _lookahead, std::string _label="");
  inline uint64_t pos() const {return c_pos;};
  inline uint64_t len() const {return c_len;};
  inline bool eof() const {return c_pos >= c_len;};
  inline Reader &skip(int64_t _len) {c_pos += _len; return *this;};
  Reader& fetch(int8_t& _val);
  Reader& fetch(int32_t& _val);
  Reader& fetch(int64_t& _val);
  Reader& fetch(float& _val);
  Reader& fetch(Vector2& _val);
  Reader& fetch(Vector3& _val);
  Reader& fetch(Vector4& _val);
  Reader& fetch(std::string& _val);
  char* pass(uint64_t _len);

  Reader& dump(const std::string _file);

  // quickhand ops
  inline Reader& operator()(int8_t& _v) {return fetch(_v);};
  inline Reader& operator()(int32_t& _v) {return fetch(_v);};
  inline Reader& operator()(int64_t& _v) {return fetch(_v);};
  inline Reader& operator()(float& _v) {return fetch(_v);};
  inline Reader& operator()(Vector2& _v) {return fetch(_v);};
  inline Reader& operator()(Vector3& _v) {return fetch(_v);};
  inline Reader& operator()(Vector4& _v) {return fetch(_v);};
  inline Reader& operator()(std::string& _v) {return fetch(_v);};

private:
  void lencheck(int64_t _l);

protected:
  char *c_buffer;
  uint64_t c_len;
  uint64_t c_pos;
};

class ChunkReader: public Reader {
  ChunkReader() = delete;
  ChunkReader(const Reader&) = delete;
public:
  ChunkReader(Reader &);
  virtual ~ChunkReader();

private:
  Reader &c_reader;
};

#endif
