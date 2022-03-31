
#include "World.hh"

#include "Trace.hh"
#include "Exception.hh"
#include "FGObjectHeader.hh"
#include "misc.hh"
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
//#include "FG.hh"

#include <set>
#include <iostream>
#include <fstream>
#include <vector>

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
  TRACE;
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
#ifdef SFT_DEBUG
  printf("New world:\n%s", c_headers.str().c_str());
#endif
}

World::~World() {
}

void World::deserialize(Reader &_reader) {
  TRACE;
  std::vector<SaveableSP> objects;
  _reader.skip(4).fetch(c_world_object_count);
  t.detail("world object count", c_world_object_count);

  objects.resize(c_world_object_count);

  // read world objects
  int32_t objtype;
  std::string name, proptype, instance;
  std::string match0, match1, match2;
  for (int i=0; i<c_world_object_count; ++i) {

    FGObjectHeader header(_reader);

    //printf("Read object header(%i/%i):\n%s", i, c_world_object_count, header.str().c_str());

    if ( header.isEntity() ) {
      //printf("Entity: %s\n", header.FGObjectType().c_str());
      //printf("%s", header.str().c_str());
      if ( header.FGObjectType() == "Build_ConveyorBeltMk1_C" ) {
	auto obj = std::make_shared<FGConveyorBeltMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorBeltMk2_C" ) {
	auto obj = std::make_shared<FGConveyorBeltMk2>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorBeltMk3_C" ) {
	auto obj = std::make_shared<FGConveyorBeltMk3>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorBeltMk4_C" ) {
	auto obj = std::make_shared<FGConveyorBeltMk4>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorBeltMk5_C" ) {
	auto obj = std::make_shared<FGConveyorBeltMk5>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorLiftMk1_C" ) {
	auto obj = std::make_shared<FGConveyorLiftMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorLiftMk2_C" ) {
	auto obj = std::make_shared<FGConveyorLiftMk2>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorLiftMk3_C" ) {
	auto obj = std::make_shared<FGConveyorLiftMk3>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorLiftMk4_C" ) {
	auto obj = std::make_shared<FGConveyorLiftMk4>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorLiftMk5_C" ) {
	auto obj = std::make_shared<FGConveyorLiftMk5>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belts[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorAttachmentMerger_C" ) {
	auto obj = std::make_shared<FGConveyorAttachmentMerger>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belt_logics[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorAttachmentSplitter_C" ) {
	auto obj = std::make_shared<FGConveyorAttachmentSplitter>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belt_logics[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConveyorAttachmentSplitterSmart_C" ) {
	auto obj = std::make_shared<FGConveyorAttachmentSplitterSmart>(_reader, header);
	c_entities[header.instance()] = obj;
	c_belt_logics[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_AssemblerMk1_C" ) {
	auto obj = std::make_shared<FGAssemblerMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_Blender_C" ) {
	auto obj = std::make_shared<FGBlender>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ConstructorMk1_C" ) {
	auto obj = std::make_shared<FGConstructorMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_FoundryMk1_C" ) {
	auto obj = std::make_shared<FGFoundryMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_HadronCollider_C" ) {
	auto obj = std::make_shared<FGHadronCollider>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ManufacturerMk1_C" ) {
	auto obj = std::make_shared<FGManufacturerMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_OilRefinery_C" ) {
	auto obj = std::make_shared<FGOilRefinery>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_Packager_C" ) {
	auto obj = std::make_shared<FGPackager>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_SmelterMk1_C" ) {
	auto obj = std::make_shared<FGSmelterMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_GeneratorCoal_C" ) {
	auto obj = std::make_shared<FGGeneratorCoal>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_GeneratorFuel_C" ) {
	auto obj = std::make_shared<FGGeneratorFuel>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_GeneratorNuclear_C" ) {
	auto obj = std::make_shared<FGGeneratorNuclear>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_ResourceSink_C" ) {
	auto obj = std::make_shared<FGResourceSink>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_SpaceElevator_C" ) {
	auto obj = std::make_shared<FGSpaceElevator>(_reader, header);
	c_entities[header.instance()] = obj;
	c_iounits[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_DroneStation_C" ) {
	auto obj = std::make_shared<FGDroneStation>(_reader, header);
	c_entities[header.instance()] = obj;
	c_storage_units[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_StorageContainerMk1_C" ) {
	auto obj = std::make_shared<FGStorageContainerMk1>(_reader, header);
	c_entities[header.instance()] = obj;
	c_storage_units[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_StorageContainerMk2_C" ) {
	auto obj = std::make_shared<FGStorageContainerMk2>(_reader, header);
	c_entities[header.instance()] = obj;
	c_storage_units[header.instance()] = obj;
	objects[i] = obj;
      } else if ( header.FGObjectType() == "Build_TrainDockingStation_C" ) {
	auto obj = std::make_shared<FGTrainDockingStation>(_reader, header);
	c_entities[header.instance()] = obj;
	c_storage_units[header.instance()] = obj;
	objects[i] = obj;
      } else {
	auto obj = std::make_shared<FGGenericEntity>(_reader, header);
	c_entities[header.instance()] = obj;
	objects[i] = obj;
	//printf(" !!! Unhandled entity object type\nHeaders:\n%s", header.str().c_str());
	//EXCEPTION(strprintf("Unhandled objectype: %s", header.FGObjectType().c_str()));
      }
    } else if ( header.isComponent() ) {
      if ( false ) {
      } else {
	auto obj = std::make_shared<FGGenericComponent>(_reader, header);
	c_components[header.instance()] = obj;
      }
    } else {
#ifdef SFT_DEBUG
      t.debug();
      _reader.debug(32, "unknown object").dump("/tmp/world-unknown-1.dump");
#endif
      EXCEPTION("Unknown object type");
    }

  }
  t.printf("Loaded %i world objects\n", c_world_object_count);
  t.printf("Belts loaded: %lu\n", c_belts.size());
  t.printf("Beltlogics loaded: %lu\n", c_belt_logics.size());
  t.printf("IOUnits loaded: %lu\n", c_iounits.size());
  t.printf("StorageUnits loaded: %lu\n", c_storage_units.size());

  // associate components with their entities
  t.printf("Associating components with their entites\n");
  for (auto it: c_components) {
    auto entit = c_entities.find(it.second->parentEntityName());
    if ( entit == c_entities.end() ) {
      t.printf("Component %s has no parent %s\n", it.first.c_str(),
	       it.second->parentEntityName().c_str());
      continue;
    }
    entit->second->associate(it.second);
  }
  t.printf("Components associated\n");

  _reader(c_world_object_property_count);
  printf("World object property count: %i\n", c_world_object_property_count);

  int32_t propsize;
  for ( int32_t i=0; i<c_world_object_property_count; ++i) {
    _reader(propsize);
    Reader propreader(_reader, propsize, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    try {
      objects[i]->deserializeProperties(propreader);
    } catch (Exception &e) {
      printf("World::deserializeProperties(%i/%i) Exception: %s\n",
	     i, c_world_object_property_count, e.what());
      return;
    }
  }

#if 0
  // now dump the fgobjtypes
  std::set<std::string> fgobjtypes;
  for (auto it: c_entities) {
    fgobjtypes.insert(it.second->FGObjectType());
  }
  // and dump them
  {
    std::ofstream of;
    of.open("/tmp/fgobjtypes");
    for (auto it: fgobjtypes) {
      of << it << std::endl;
    }
    of.close();
  }
#endif
  
}

std::string World::str() const {
  return strprintf("World %s\n", c_headers.sessionName().c_str());
}

