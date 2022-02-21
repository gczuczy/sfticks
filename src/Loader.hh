#include <string>
#include <stdint.h>

class Loader {
public:
  Loader(const std::string &_file);
  ~Loader();

  void parse();

private:
  class Reader {
  public:
    Reader() = delete;
    Reader(const Reader&) = delete;
    Reader(char *_buffer, uint64_t _len);
    virtual ~Reader();

    int8_t fetch_int8(uint64_t _pos) const;
    int32_t fetch_int32(uint64_t _pos) const;
    int64_t fetch_int64(uint64_t _pos) const;
    std::string fetch_string(uint64_t pos) const;
  private:
    char *c_buffer;
    uint64_t c_len;
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
