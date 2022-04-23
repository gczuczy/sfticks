
#include "FGComponent.hh"
#include "FGEntity.hh"
#include "Exception.hh"
#include "FGObjectLibrary.hh"

#include <typeinfo>

namespace FG {

  Component::Component(ComponentType _comptype, Reader& _reader, ObjectHeader& _fgoh)
    : ObjectHeader(_fgoh), BaseObject(ObjectType::COMPONENT), c_comptype(_comptype) {
    deserialize(_reader);
  }

  Component::~Component() {
    //printf("Component dtor\n%s", str().c_str());
  }

  void Component::deserializeProperties(Reader &_reader) {
    //TRACE;
    loadProperties(_reader);
  }

  std::string Component::vtypename() {
    return typeid(*this).name();
  }

  void Component::deserialize(Reader &_reader) {
    _reader(c_parent_entity_name);
  }

  void Component::resolveParent() {
    if ( c_parent ) return;
    if ( c_parent_entity_name.size() == 0 )
      EXCEPTION("Empty parent entity");

    c_parent = std::static_pointer_cast<Entity>(ObjectLibrary::getInstance()->lookup(c_proptype,
										     c_parent_entity_name));
  }
}
