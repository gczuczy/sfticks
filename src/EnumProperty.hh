
#ifndef SFT_ENUMPROPERTY_HH
#define SFT_ENUMPROPERTY_HH

#include "PropertyInterface.hh"
#include "Exception.hh"
#include "FGEnums.hh"

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
      c_value = EnumDict<T>::fromstr(valuestr);
    }

  private:
    std::string c_enumtypestr;
    T& c_value;
  };

}

#endif
