
#ifndef SFT_WORLD_H
#define SFT_WORLD_H

#include <stdint.h>
#include <string>
#include <map>
#include <set>
#include <memory>

#include "Saveable.hh"
#include "FGEntity.hh"
#include "FGComponent.hh"
#include "FGConveyorBelt.hh"
#include "FGConveyorBeltLogic.hh"
#include "FGIOUnit.hh"
#include "FGStorageUnit.hh"

class World: public Saveable {
public:
  class Header: public Saveable {
  public:
    Header();
    virtual ~Header();

    virtual void deserialize(Reader &_reader);
    virtual void deserializeProperties(Reader &_reader) {};
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

    virtual std::string str() const;

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
private:
  typedef std::function<FGComponentSP(Reader&, FGObjectHeader&)> component_callback;

public:
  World()=delete;
  World(Header& _header);
  virtual ~World();

  virtual void deserialize(Reader &_reader);
  virtual void deserializeProperties(Reader &_reader) {};
  virtual std::string str() const;

private:
  template<class T>
  void defineComponent() {
    c_compdefs[T::pathname] = T::instantiate;
  }

private:
  Header c_headers;
  int32_t c_world_object_count, c_world_object_property_count, c_world_collected_object_count;

  // component defintions
  std::map<std::string, component_callback> c_compdefs;

  // complete maps for direct lookups
  // this includes all objects
  std::map<std::string, std::shared_ptr<FGEntity> > c_entities;
  // components
  std::map<std::string, FGComponentSP > c_components;
  // belts
  std::map<std::string, FGConveyorBeltSP> c_belts;
  // belt logics. splitters/mergers/etc
  std::map<std::string, FGConveyorBeltLogicSP> c_belt_logics;
  // IO Units
  std::map<std::string, FGIOUnitSP> c_iounits;
  // storage units
  std::map<std::string, FGStorageUnitSP> c_storage_units;
};

#endif
