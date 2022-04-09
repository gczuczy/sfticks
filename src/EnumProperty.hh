
#ifndef SFT_ENUMPROPERTY_HH
#define SFT_ENUMPROPERTY_HH

#include "PropertyInterface.hh"
#include "Exception.hh"
#include "FGEnums.hh"

#include <map>

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
    for (auto& it: c_strmap) {
      if ( it.second == valuestr ) {
	c_value = it.first;
	return;
      }
    }
    EXCEPTION(std::string("Value not found: ")+valuestr);
  }

private:
  static std::map<T, std::string> c_strmap;
  std::string c_enumtypestr;
  T& c_value;
};

template<>
std::map<ETrainPlatformDockingStatus, std::string> EnumProperty<ETrainPlatformDockingStatus>::c_strmap;

template<>
std::map<EFactoryConnectionDirection, std::string> EnumProperty<EFactoryConnectionDirection>::c_strmap;


#if 0
extern template
EnumProperty<ETrainPlatformDockingStatus>::EnumProperty(const std::string& _name, ETrainPlatformDockingStatus& _value, int32_t _index=0);
extern template
std::map<ETrainPlatformDockingStatus, std::string> EnumProperty<ETrainPlatformDockingStatus>::c_strmap;
#endif
#endif
