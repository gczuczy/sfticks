
#ifndef SFT_ENUMPROPERTY_HH
#define SFT_ENUMPROPERTY_HH

#include "FG/PropertyInterface.hh"
#include "SFT/Exception.hh"
#include "FG/Enums.hh"

//#include <stdio.h>

#include <map>

namespace FG {

  template<typename T>
  class EnumProperty: public PropertyInterface {
  public:
    EnumProperty() = delete;
    EnumProperty(const std::string& _name, T& _value, int32_t _index=0);
    virtual ~EnumProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size) {
      std::string typestr;
      _reader(typestr).skip(1);

      // check the typestr
      if ( c_enumtypestr != typestr )
	EXCEPTION(std::string("Invalid type: ")+typestr+std::string(" for type: ")+c_enumtypestr);
      Reader data(_reader, _size);
      deserializeData(data);
    };

    virtual void deserializeData(Reader& _reader) {
      std::string valuestr;
      _reader(valuestr);
#if 0
      if ( c_enumtypestr == "EFactoryConnectionDirection" )
	throw std::exception();
#endif
      //printf("Setting %s enumtype %s from value '%s'\n", name().c_str(), c_enumtypestr.c_str(), valuestr.c_str());
      c_value = EnumDict<T>::fromstr(valuestr);
      //printf(" - to: '%s'\n", EnumDict<T>::tostr(c_value).c_str());
    }

  private:
    std::string c_enumtypestr;
    T& c_value;
  };

}

#endif
