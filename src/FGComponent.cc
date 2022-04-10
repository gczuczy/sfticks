
#include "FGComponent.hh"
#include "Exception.hh"

#include <typeinfo>

namespace FG {

  Component::Component(ComponentType _comptype, Reader& _reader, ObjectHeader& _fgoh)
    : ObjectHeader(_fgoh), c_comptype(_comptype) {
    deserialize(_reader);
  }

  Component::~Component() {
  }

  void Component::deserializeProperties(Reader &_reader) {
    //TRACE;
    loadProperties(_reader);
  }

  void Component::deserialize(Reader &_reader) {
    _reader(c_parent_entity_name);
  }

  std::string Component::vtypename() {
    return typeid(*this).name();
  }
}
