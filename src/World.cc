
#include "World.hh"

#include "Trace.hh"
#include "Exception.hh"
#include "FGObjectHeader.hh"
#include "misc.hh"
#include "FGGenericEntity.hh"
#include "FGGenericComponent.hh"

#include <set>
#include <iostream>
#include <fstream>

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
    strprintf("Save date: %i ticks\n", c_save_version) +
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
  _reader.skip(4).fetch(c_world_object_count);
  t.detail("world object count", c_world_object_count);

  // read world objects
  int32_t objtype;
  std::string name, proptype, instance;
  std::string match0, match1, match2;
  for (int i=0; i<c_world_object_count; ++i) {

    FGObjectHeader header(_reader);

    printf("Read object header(%i/%i):\n%s", i, c_world_object_count, header.str().c_str());

    if ( header.isEntity() ) {
      printf("Entity: %s\n", header.FGObjectType().c_str());
      if ( false ) {
      } else {
	auto obj = std::make_shared<FGGenericEntity>(_reader, header);
	c_entities[header.instance()] = obj;
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
