
#ifndef SFT_GENERICARRAYPROPERTY_H
#define SFT_GENERICARRAYPROPERTY_H

#include "PropertyInterface.hh"

namespace FG {

  /*
    This class is intended to hold the complete array data
    internally, without actually parsing it
  */
  class GenericArrayProperty: public PropertyInterface {
  public:
    GenericArrayProperty() = delete;
    GenericArrayProperty(const std::string& _name, int32_t _index=0);
    virtual ~GenericArrayProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size);
    virtual void deserializeData(Reader& _reader);

  private:
    std::string c_arraytypestr;
    std::string c_data;
    int32_t c_count;
  };

}

#endif
