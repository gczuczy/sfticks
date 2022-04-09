
#ifndef SFT_BOOLPROPERTY_H
#define SFT_BOOLPROPERTY_H

#include "PropertyInterface.hh"

namespace FG {

  class BoolProperty: public PropertyInterface {
  public:
    BoolProperty() = delete;
    BoolProperty(const std::string& _name, bool& _value, int32_t _index=0);
    virtual ~BoolProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size);
    virtual void deserializeData(Reader& _reader);

  private:
    bool& c_value;
  };

}

#endif
