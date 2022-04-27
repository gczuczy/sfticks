
#include "World.hh"

#include "Trace.hh"
#include "Exception.hh"
#include "FGObjectHeader.hh"
#include "misc.hh"

// Entities
#include "FGGenericEntity.hh"
#include "FGGenericComponent.hh"
#include "FGConveyorBeltMk1.hh"
#include "FGConveyorBeltMk2.hh"
#include "FGConveyorBeltMk3.hh"
#include "FGConveyorBeltMk4.hh"
#include "FGConveyorBeltMk5.hh"
#include "FGConveyorLiftMk1.hh"
#include "FGConveyorLiftMk2.hh"
#include "FGConveyorLiftMk3.hh"
#include "FGConveyorLiftMk4.hh"
#include "FGConveyorLiftMk5.hh"
#include "FGConveyorAttachmentMerger.hh"
#include "FGConveyorAttachmentSplitter.hh"
#include "FGConveyorAttachmentSplitterSmart.hh"
#include "FGMinerMk1.hh"
#include "FGMinerMk2.hh"
#include "FGMinerMk3.hh"
#include "FGAssemblerMk1.hh"
#include "FGBlender.hh"
#include "FGConstructorMk1.hh"
#include "FGFoundryMk1.hh"
#include "FGHadronCollider.hh"
#include "FGManufacturerMk1.hh"
#include "FGOilRefinery.hh"
#include "FGPackager.hh"
#include "FGSmelterMk1.hh"
#include "FGGeneratorCoal.hh"
#include "FGGeneratorFuel.hh"
#include "FGGeneratorNuclear.hh"
#include "FGResourceSink.hh"
#include "FGSpaceElevator.hh"
#include "FGDroneStation.hh"
#include "FGStorageContainerMk1.hh"
#include "FGStorageContainerMk2.hh"
#include "FGTrainDockingStation.hh"
#include "FGTruckStation.hh"
//#include "FG.hh"

// components
#include "FGFactoryConnectionComponent.hh"
#include "FGInventoryComponent.hh"
#include "FGPowerInfoComponent.hh"

#include "FGObjectLibrary.hh"

#include <set>
#include <iostream>
#include <fstream>
#include <vector>

namespace FG {

  World::Header::Header():
    c_header_version(0),
    c_save_version(0),
    c_build_version(0),
    c_world_type(""),
    c_world_properties(""),
    c_session_name(""),
    c_playtime(0),
    c_save_date(0),
    c_visiblity(0),
    c_editor_object_version(0),
    c_mod_metadata(""),
    c_mod_flags(0) {
  }

  World::Header::~Header() {
  }

  void World::Header::deserialize(Reader &_reader) {
    //TRACE;
    _reader
      .fetch(c_header_version)
      .fetch(c_save_version)
      .fetch(c_build_version)
      .fetch(c_world_type)
      .fetch(c_world_properties)
      .fetch(c_session_name)
      .fetch(c_playtime)
      .fetch(c_save_date)
      .fetch(c_visiblity)
      .fetch(c_editor_object_version)
      .fetch(c_mod_metadata)
      .fetch(c_mod_flags);
  }

  std::string World::Header::str() const {
    return strprintf("Header version: %i\n", c_header_version) +
      strprintf("Save version: %i\n", c_save_version) +
      strprintf("Build version: %i\n", c_build_version) +
      strprintf("World type: %s\n", c_world_type.c_str()) +
      strprintf("World properties: %s\n", c_world_properties.c_str()) +
      strprintf("Session name: %s\n", c_session_name.c_str()) +
      strprintf("Play time: %i seconds\n", c_playtime) +
      strprintf("Save date: %li ticks\n", c_save_date) +
      strprintf("Visibility: %i\n", c_visiblity) +
      strprintf("Editor Object Version: %i\n", c_editor_object_version) +
      strprintf("Mod metadata: %s\n", c_mod_metadata.c_str()) +
      strprintf("Mod flags: %i\n", c_mod_flags);
  }

  World::World(Header& _header): c_headers(_header) {
    printf("Brave New world:\n%s", c_headers.str().c_str());
    ObjectLibrary::getInstance()->addDictionary(c_headers.worldType(), *this);
    // entity definitions
    // belts & logics
    registerEntityType<ConveyorBeltMk1>();
    registerEntityType<ConveyorBeltMk2>();
    registerEntityType<ConveyorBeltMk3>();
    registerEntityType<ConveyorBeltMk4>();
    registerEntityType<ConveyorBeltMk5>();
    registerEntityType<ConveyorLiftMk1>();
    registerEntityType<ConveyorLiftMk2>();
    registerEntityType<ConveyorLiftMk3>();
    registerEntityType<ConveyorLiftMk4>();
    registerEntityType<ConveyorLiftMk5>();
    registerEntityType<ConveyorAttachmentMerger>();
    registerEntityType<ConveyorAttachmentSplitter>();
    registerEntityType<ConveyorAttachmentSplitterSmart>();
    // miners
    registerEntityType<MinerMk1>();
    registerEntityType<MinerMk2>();
    registerEntityType<MinerMk3>();
    // manufacturing units
    registerEntityType<AssemblerMk1>();
    registerEntityType<ConstructorMk1>();
    registerEntityType<ManufacturerMk1>();
    registerEntityType<Blender>();
    registerEntityType<HadronCollider>();
    registerEntityType<FoundryMk1>();
    registerEntityType<OilRefinery>();
    registerEntityType<Packager>();
    registerEntityType<SmelterMk1>();
    // generators
    registerEntityType<GeneratorCoal>();
    registerEntityType<GeneratorFuel>();
    registerEntityType<GeneratorNuclear>();
    // sinks
    registerEntityType<SpaceElevator>();
    registerEntityType<ResourceSink>();
    // logistics units
    registerEntityType<DroneStation>();
    registerEntityType<TrainDockingStation>();
    registerEntityType<TruckStation>();
    // stroage
    registerEntityType<StorageContainerMk1>();
    registerEntityType<StorageContainerMk2>();

    // component definitions
    registerComponentType<FactoryConnectionComponent>();
    registerComponentType<InventoryComponent>();
    registerComponentType<PowerInfoComponent>();
    //registerComponentType<Component>();
  }

  World::~World() {
    c_world_collected_objects.clear();
    c_storage_units.clear();
    c_iounits.clear();
    c_belt_logics.clear();
    c_belts.clear();
    c_entities.clear();
    c_components.clear();
    c_allobjects.clear();
  }

  void World::deserialize(Reader &_reader) {
    //TRACE;
    std::vector<SaveableSP> objects;
    _reader.skip(4).fetch(c_world_object_count);
    //t.detail("world object count", c_world_object_count);

    _reader.setThrow(false);
    objects.resize(c_world_object_count);

    // read world objects
    int32_t objtype;
    std::string name, proptype, instance;
    std::string match0, match1, match2;
    for (int i=0; i<c_world_object_count; ++i) {

      ObjectHeader header(_reader);

      //printf("Read object header(%i/%i):\n%s", i, c_world_object_count, header.str().c_str());

      std::map<std::string, entity_callback>::iterator eit;
      if ( header.isEntity() ) {
	//printf("Entity: %s\n", header.ObjectType().c_str());
	//printf("%s", header.str().c_str());
	if ( (eit = c_entitydefs.find(header.className())) != c_entitydefs.end() ) {
	  objects[i] = eit->second(std::ref(_reader), std::ref(header));
	} else {
	  auto obj = std::make_shared<GenericEntity>(_reader, header);
	  c_entities[header.instance()] = obj;
	  objects[i] = obj;
	  c_allobjects[obj->instance()] = obj;
	  //printf(" !!! Unhandled entity object type\nHeaders:\n%s", header.str().c_str());
	  //EXCEPTION(strprintf("Unhandled objectype: %s", header.objectType().c_str()));
	}
      } else if ( header.isComponent() ) {
	ComponentSP obj;
	auto it = c_compdefs.find(header.name());
	if ( it != c_compdefs.end() ) {
	  obj = it->second(std::ref(_reader), std::ref(header));
	} else {
	  obj = std::make_shared<GenericComponent>(_reader, header);
	}
	c_components[header.instance()] = obj;
	objects[i] = obj;
	c_allobjects[obj->instance()] = obj;
      } else {
#ifdef SFT_DEBUG
	//t.debug();
	_reader.debug(32, "unknown object").dump("/tmp/world-unknown-1.dump");
#endif
	EXCEPTION("Unknown object type");
      }

    }
    printf("Loaded %i world objects\n", c_world_object_count);
    printf("Belts loaded: %lu\n", c_belts.size());
    printf("Beltlogics loaded: %lu\n", c_belt_logics.size());
    printf("IOUnits loaded: %lu\n", c_iounits.size());
    printf("StorageUnits loaded: %lu\n", c_storage_units.size());

    _reader(c_world_object_property_count);
    printf("World object property count: %i\n", c_world_object_property_count);

    int32_t propsize;
    for ( int32_t i=0; i<c_world_object_property_count; ++i) {
      //printf("%i/%i\n%s", i, c_world_object_property_count, objects[i]->str().c_str());
      _reader(propsize);
      Reader propreader(_reader, propsize, __FILE__, __LINE__, __PRETTY_FUNCTION__);
      try {
	objects[i]->deserializeProperties(propreader);
      }
      catch (SFT::Exception &e) {
	printf("World::deserializeProperties(%i/%i) Exception: %s\n",
	       i, c_world_object_property_count, e.what());
	printf("%s\n", objects[i]->str().c_str());
	return;
      }
      catch (std::exception &e) {
	printf("Generic exception: %s\n", e.what());
	return;
      }
    }
    printf("Finished deserializing properties\n");

    // associate components with their entities
    printf("Associating components with their entites\n");
    for (auto it: c_components) {
      auto entit = c_entities.find(it.second->parentEntityName());
      if ( entit == c_entities.end() ) {
	printf("Component %s has no parent %s\n", it.first.c_str(),
	       it.second->parentEntityName().c_str());
	continue;
      }
      try {
	entit->second->associate(it.second);
      }
      catch (SFT::Exception& e) {
	printf("Caught exception: %s\n", e.what());
	return;
      }
    }
    printf("Components associated\n");

    _reader(c_world_collected_object_count);
    printf("World collected object count: %i\n", c_world_collected_object_count);
    for (int32_t i=0; i<c_world_collected_object_count; ++i) {
      std::string level,path;
      _reader(level)(path);
      //printf("%s / %s\n", level.c_str(), path.c_str());
      c_world_collected_objects.insert(ObjectReference(level, path));
    }

    // the rest seems to be spawn data, which is not important to
    // the current scope of the project
    //_reader.dump("/tmp/remnants.dump", _reader.len()-_reader.pos());
  }

  std::string World::str() const {
    return strprintf("World %s\n", c_headers.sessionName().c_str());
  }

  BaseObjectSP World::lookupObject(const std::string& _pathname) {
    // first look in entities
    {
      auto it = c_entities.find(_pathname);
      if ( it != c_entities.end() ) return it->second;
    }
    // then components
    {
      auto it = c_components.find(_pathname);
      if ( it != c_components.end() ) return it->second;
    }
    return nullptr;
  }
}
