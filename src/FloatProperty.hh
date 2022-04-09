
#ifndef SFT_FLOATPROPERTY_H
#define SFT_FLOATPROPERTY_H

#include "PropertyInterface.hh"

namespace FG {

  class FloatProperty: public PropertyInterface {
  public:
    FloatProperty() = delete;
    FloatProperty(const std::string& _name, float& _value, int32_t _index=0);
    virtual ~FloatProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size);
    virtual void deserializeData(Reader& _reader);

  private:
    float& c_value;
  };

}

#endif
