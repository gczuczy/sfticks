#include <string>
#include <stdint.h>

class Loader {
public:
  Loader(const std::string &_file);
  ~Loader();

  void parse();

private:
  class ChunkReader;
  class Reader {
  protected:
    Reader();
  public:
    Reader(const Reader&) = delete;
    Reader(char *_buffer, uint64_t _len);
    virtual ~Reader();

    Reader& debug(uint64_t _lookahead);
    inline uint64_t pos() const {return c_pos;};
    inline uint64_t len() const {return c_len;};
    inline bool eof() const {return c_pos >= c_len;};
    Reader& fetch_int8(int8_t& _val);
    Reader& fetch_int32(int32_t& _val);
    Reader& fetch_int64(int64_t& _val);
    Reader& fetch_string(std::string& _val);
    char* pass(uint64_t _len);

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

private:
  std::string c_filename;
  int c_fd;
  uint64_t c_savesize;
  char *c_save;

  // headers
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
};
