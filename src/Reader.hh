
#ifndef SFT_READERS_H
#define  SFT_READERS_H

#include <stdint.h>

#include <string>
#include <map>

#include "vectors.hh"

std::string hexhash(const std::string &);

class ChunkReader;
class Reader {
protected:
  Reader();
public:
  Reader(const Reader&) = delete;
  Reader(Reader& _parent, uint64_t len, std::string _file="", int _line=0, std::string _comment="");
  Reader(Reader& _parent, const std::string _mark, uint64_t len, std::string _file="", int _line=0, std::string _comment="");
  Reader(char *_buffer, uint64_t _len);
  virtual ~Reader() noexcept(false);

  Reader& debug(uint64_t _lookahead, std::string _label="");
  inline uint32_t id() const {return c_id;};
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
  char* pass(const std::string& _mark, uint64_t _len);

  inline Reader& mark(const std::string _mark) {c_marks[_mark] = c_pos; return *this;};
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
  uint64_t offset(const std::string& _mark);
  inline uint64_t offset(uint64_t _pos) const {return c_pos - _pos;};
  static bool c_in_exception;
  static uint32_t c_id_idx;

protected:
  uint32_t c_id;
  std::string c_file, c_comment, c_parent_file, c_parent_comment;
  int c_line, c_parent_line;
  uint32_t c_parent_id;
  char *c_buffer;
  uint64_t c_len;
  uint64_t c_pos;
  std::map<std::string, uint64_t> c_marks;
  bool c_hasparent;
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
