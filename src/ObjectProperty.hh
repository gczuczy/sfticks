
#ifndef SFT_OBJECTPROPERTY_H
#define SFT_OBJECTPROPERTY_H

#include "PropertyInterface.hh"
#include "ObjectReference.hh"

#include <memory>

namespace FG {

  class ObjectProperty: public PropertyInterface {
  public:
    struct NestedHeader {
    };
    typedef ObjectReference value_type;
  public:
    ObjectProperty() = delete;
    ObjectProperty(const std::string& _name, ObjectReference& _value, int32_t _index=0, bool _debug=false);
    virtual ~ObjectProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size);
    virtual void deserializeData(Reader& _reader);

    static void deserializeNestedHeaders(Reader& _reader, NestedHeader& _nh);

  private:
    ObjectReference& c_value;
    bool c_debug;
  };

}

#endif
