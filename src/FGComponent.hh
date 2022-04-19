
#ifndef SFT_FGCOMPONENT_H
#define SFT_FGCOMPONENT_H

#include "FGObjectHeader.hh"

#include <stdint.h>
#include <string>
#include <memory>

#include "vectors.hh"
#include "misc.hh"

namespace FG {

  enum class ComponentType: int32_t {
    Generic=-1,
    FactoryConnection=0,
    Inventory,
  };

  class Entity;
  class Component: public ObjectHeader {
    Component()=delete;
  public:
    Component(ComponentType _comptype, Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Component();

    inline ComponentType componentType() const {return c_comptype;};
    inline std::string parentEntityName() const {return c_parent_entity_name;};
    inline std::shared_ptr<Entity> parent() { resolveParent(); return c_parent;};
    inline std::string instanceName() const {return strprintf("%s_%i", c_component_name.c_str(), c_component_instanceid);};

    virtual void deserializeProperties(Reader &_reader);
    virtual std::string vtypename();
    virtual std::string compdetails()=0;
  private:
    virtual void deserialize(Reader &_reader);
    void resolveParent();

  protected:
    std::string c_parent_entity_name;

  private:
    ComponentType c_comptype;
    std::shared_ptr<Entity> c_parent;
  };

  typedef std::shared_ptr<Component> ComponentSP;

}

#endif
