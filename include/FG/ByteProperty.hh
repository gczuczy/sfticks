
#ifndef SFT_BYTEPROPERTY_H
#define SFT_BYTEPROPERTY_H

#include "FG/PropertyInterface.hh"

namespace FG {

  class ByteProperty: public PropertyInterface {
  public:
    typedef int8_t value_type;
    ByteProperty() = delete;
    ByteProperty(const std::string& _name, value_type& _value, int32_t _index=0);
    virtual ~ByteProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size);
    virtual void deserializeData(Reader& _reader);

  private:
    value_type& c_value;
  };

}

#endif
