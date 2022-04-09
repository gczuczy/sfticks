
#ifndef SFT_FGENTITY_H
#define SFT_FGENTITY_H

#include "FGObjectHeader.hh"

#include <stdint.h>
#include <string>
#include <map>
#include <functional>
#include <memory>

#include "vectors.hh"
#include "FGComponent.hh"

namespace FG {

  /*
    Build_FrackingExtractor_C
    Build_FrackingSmasher_C
    https://satisfactory.fandom.com/wiki/Resource_Well_Pressurizer#Pressurizer
  */
  // sftick's scope is everything with belts. So only belt-related
  // entites are being implemented for now
  enum class EntityType : int32_t {
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

  class Entity: public ObjectHeader {
  protected:
    typedef std::function<void(ComponentSP&)> compreg_func;
    // constructors/destructors
  private:
    Entity()=delete;
  public:
    Entity(EntityType _et, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Entity();

    Entity& associate(ComponentSP _component);
    inline EntityType entityType() const {return c_entity_type;};
    inline const std::map<std::string, ComponentSP> components() const { return c_components;};

  private:
    virtual void deserialize(Reader &_reader);

  protected:
    template<class T>
    void registerComponent(const std::string& _name, std::shared_ptr<T>& _var) {
      c_compregs[_name] = [&](ComponentSP& _comp)->void {
	_var = std::reinterpret_pointer_cast<T>(_comp);
      };
    };

  private:
    EntityType c_entity_type;
    // component name, callback to place it
    std::map<std::string, compreg_func> c_compregs;

  protected:
    int32_t c_needtransform;
    Vector4 c_rotation;
    Vector3 c_position, c_scale;
    int32_t c_placedinlevel;
    std::string c_parent_object_root;
    std::string c_parent_object_name;

    std::map<std::string, ComponentSP> c_components;
  };
  typedef std::shared_ptr<Entity> EntitySP;

}

#endif
