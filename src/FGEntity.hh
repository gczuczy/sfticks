
#ifndef SFT_FGENTITY_H
#define SFT_FGENTITY_H

#include "FGObjectHeader.hh"

#include <stdint.h>
#include <string>
#include <map>

#include "vectors.hh"
#include "FGComponent.hh"

/*
Build_FrackingExtractor_C
Build_FrackingSmasher_C
https://satisfactory.fandom.com/wiki/Resource_Well_Pressurizer#Pressurizer
 */
// sftick's scope is everything with belts. So only belt-related
// entites are being implemented for now
enum class FGEntityType : int32_t {
  GenericEntity = 0,
  // belts
  ConveyorBeltMk1,
  ConveyorBeltMk2,
  ConveyorBeltMk3,
  ConveyorBeltMk4,
  ConveyorBeltMk5,
  ConveyorLiftMk1,
  ConveyorLiftMk2,
  ConveyorLiftMk3,
  ConveyorLiftMk4,
  ConveyorLiftMk5,
  ConveyorAttachmentMerger,
  ConveyorAttachmentSplitterSmart,
  ConveyorAttachmentSplitter,
  // miners
  MinerMk1,
  MinerMk2,
  MinerMk3,
  // production units, "converters"
  AssemblerMk1,
  Blender,
  ConstructorMk1,
  FoundryMk1,
  HadronCollider,
  ManufacturerMk1,
  OilRefinery,
  Packager,
  SmelterMk1,
  // generators
  GeneratorCoal,
  GeneratorFuel,
  GeneratorNuclear,
  // sinks
  ResourceSink,
  SpaceElevator,
  // storage units and transportation
  DroneStation,
  StorageContainerMk1,
  StorageContainerMk2,
  TrainDockingStation,
};

class FGEntity: public FGObjectHeader {
  // constructors/destructors
private:
  FGEntity()=delete;
public:
  FGEntity(FGEntityType _et, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGEntity();

  FGEntity& associate(FGComponentSP _component);
  inline FGEntityType entityType() const {return c_entity_type;};

private:
  virtual void deserialize(Reader &_reader);

private:
  FGEntityType c_entity_type;

protected:
  int32_t c_needtransform;
  Vector4 c_rotation;
  Vector3 c_position, c_scale;
  int32_t c_placedinlevel;
  std::string c_parent_object_root;
  std::string c_parent_object_name;

  std::map<std::string, FGComponentSP> c_components;
};

#endif
