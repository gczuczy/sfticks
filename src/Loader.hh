
#ifndef SFT_LOADER_H
#define SFT_LOADER_H

#include <stdint.h>

#include <string>
#include <memory>

#include "World.hh"

namespace SFT {

  class Loader {
  public:
    Loader()=delete;
    Loader(const std::string& _file);
    ~Loader();

    std::shared_ptr<FG::World> parse();

  public:

  private:
    std::string c_filename;
    int c_fd;
    uint64_t c_savesize;
    char *c_save;

    // headers
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
      int32_t c_world_object_count, c_world_object_property_count, c_world_collected_object_count;
    */
  };

}

#endif
