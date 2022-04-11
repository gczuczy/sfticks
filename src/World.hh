
#ifndef SFT_WORLD_H
#define SFT_WORLD_H

#include <stdint.h>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <type_traits>

#include "Saveable.hh"
#include "FGEntity.hh"
#include "FGComponent.hh"
#include "FGConveyorBelt.hh"
#include "FGConveyorBeltLogic.hh"
#include "FGIOUnit.hh"
#include "FGMiner.hh"
#include "FGStorageUnit.hh"
#include "ObjectReference.hh"

namespace FG {

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
    typedef std::function<ComponentSP(Reader&, ObjectHeader&)> component_callback;
    typedef std::function<EntitySP(Reader&, ObjectHeader&)> entity_callback;

  public:
    World()=delete;
    World(Header& _header);
    virtual ~World();

    virtual void deserialize(Reader &_reader);
    virtual void deserializeProperties(Reader &_reader) {};
    virtual std::string str() const;

  private:
    template<class T>
    void registerComponentType() {
      for (auto it: T::pathname) {
	c_compdefs[it] = T::instantiate;
      }
    }
    template<class T>
    EntitySP instantiateEntity(Reader& _reader, ObjectHeader& _fgoh) {
      auto obj = std::make_shared<T>(_reader, _fgoh);
#if 0
      std::set<std::string> miners{"Build_MinerMk1_C", "Build_MinerMk2_C", "Build_MinerMk3_C"};
      bool miner = miners.find(_fgoh.objectType()) != miners.end();
#else
      bool miner = false;
#endif

      if (miner) printf("\n ! MINER\n%s", _fgoh.str().c_str());

      c_entities[_fgoh.instance()] = obj;
      if ( std::is_base_of<ConveyorBelt, T>::value )
	c_belts[_fgoh.instance()] = std::dynamic_pointer_cast<ConveyorBelt>(obj);

      if ( std::is_base_of<ConveyorBeltLogic, T>::value )
	c_belt_logics[_fgoh.instance()] = std::dynamic_pointer_cast<ConveyorBeltLogic>(obj);

      if ( std::is_base_of<IOUnit, T>::value ) {
	if ( miner ) printf(" - Adding to IOUnits\n");
	c_iounits[_fgoh.instance()] = std::dynamic_pointer_cast<IOUnit>(obj);
      }

      if ( std::is_base_of<StorageUnit, T>::value )
	c_storage_units[_fgoh.instance()] = std::dynamic_pointer_cast<StorageUnit>(obj);

      return obj;
    };
    template<class T>
    void registerEntityType() {
      using namespace std::placeholders;
      c_entitydefs[T::objtypename] = std::bind(&World::instantiateEntity<T>, this, _1, _2);
    }

  public:
    inline std::map<std::string, EntitySP>& entities() {return c_entities;};
    inline std::map<std::string, ConveyorBeltSP>& belts() {return c_belts;};
    inline std::map<std::string, ConveyorBeltLogicSP>& beltLogics() {return c_belt_logics;};
    inline std::map<std::string, IOUnitSP>& iounits() {return c_iounits;};
    inline std::map<std::string, StorageUnitSP>& storageUnits() {return c_storage_units;};

  private:
    Header c_headers;
    int32_t c_world_object_count, c_world_object_property_count, c_world_collected_object_count;

    // component defintions
    std::map<std::string, component_callback> c_compdefs;
    std::map<std::string, entity_callback> c_entitydefs;

    // collected objects
    std::set<ObjectReference> c_world_collected_objects;

    // complete maps for direct lookups
    // this includes all objects
    std::map<std::string, EntitySP> c_entities;
    // components
    std::map<std::string, ComponentSP > c_components;
    // belts
    std::map<std::string, ConveyorBeltSP> c_belts;
    // belt logics. splitters/mergers/etc
    std::map<std::string, ConveyorBeltLogicSP> c_belt_logics;
    // IO Units
    std::map<std::string, IOUnitSP> c_iounits;
    // storage units
    std::map<std::string, StorageUnitSP> c_storage_units;
  };

}

#endif
