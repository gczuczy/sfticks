
#ifndef SFT_READERS_H
#define  SFT_READERS_H

#include <stdint.h>

#include <string>
#include <map>
#include <memory>

#include "vectors.hh"

namespace SFT {

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
    Reader& fetch(int8_t& _val, bool _try=false);
    Reader& fetch(int32_t& _val, bool _try=false);
    Reader& fetch(int64_t& _val, bool _try=false);
    Reader& fetch(float& _val, bool _try=false);
    Reader& fetch(FG::Vector2& _val, bool _try=false);
    Reader& fetch(FG::Vector3& _val, bool _try=false);
    Reader& fetch(FG::Vector4& _val, bool _try=false);
    Reader& fetch(FG::Quat& _val, bool _try=false);
    Reader& fetch(std::string& _val, bool _try=false);
    char* pass(uint64_t _len);
    char* pass(const std::string& _mark, uint64_t _len);
    void store(std::string &_str);

    inline Reader& mark(const std::string _mark) {c_marks[_mark] = c_pos; return *this;};
    Reader& dump(const std::string _file);

    inline void setThrow(bool _throw) {c_nothrow=!_throw;};

    // quickhand ops
    inline Reader& operator()(int8_t& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(int32_t& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(int64_t& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(float& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(FG::Vector2& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(FG::Vector3& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(FG::Vector4& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(FG::Quat& _v, bool _try=false) {return fetch(_v, _try);};
    inline Reader& operator()(std::string& _v, bool _try=false) {return fetch(_v, _try);};

  private:
    bool lencheck(int64_t _l, bool _throw=true);
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
    bool c_nothrow;
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

}
typedef SFT::Reader Reader;

#endif
