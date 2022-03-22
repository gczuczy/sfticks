
#ifndef SFT_WORLD_H
#define SFT_WORLD_H

#include <stdint.h>
#include <string>
#include <map>
#include <memory>

#include "Saveable.hh"
#include "FGEntity.hh"
#include "FGComponent.hh"

class World: public Saveable {
public:
  class Header: public Saveable {
  public:
    Header();
    virtual ~Header();

    virtual void deserialize(Reader &_reader);
  public:
    inline int32_t headerVersion() const {return c_header_version;};
    inline int32_t saveVersion() const {return c_save_version;};
    inline int32_t buildVersion() const {return c_build_version;};
    inline std::string worldType() const { return c_world_type;};
    inline std::string worldProperties() const {return c_world_properties;};
    inline std::string sessionName() const {return c_session_name;};
    inline int32_t playTime() const { return c_playtime;};
    inline int64_t saveDate() const {return c_save_date;};
    inline int8_t visiblity() const {return c_visiblity;};
    inline int32_t editorObjectVersion() const {return c_editor_object_version;};
    inline std::string modMetadata() const {return c_mod_metadata;};
    inline int32_t modFlags() const {return c_mod_flags;};

    std::string str() const;

  private:
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
public:
  World()=delete;
  World(Header& _header);
  virtual ~World();

public:
  virtual void deserialize(Reader &_reader);

private:
  Header c_headers;
  int32_t c_world_object_count, c_world_object_property_count, c_world_collected_object_count;

  // complete maps for direct lookups
  // this includes all objects
  std::map<std::string, std::shared_ptr<FGEntity> > c_entities;
  // components
  std::map<std::string, FGComponentSP > c_components;
};

#endif