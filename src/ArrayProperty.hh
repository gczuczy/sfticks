
#ifndef SFT_ARRAYPROPERTY_HH
#define SFT_ARRAYPROPERTY_HH

#include "PropertyInterface.hh"
#include "Exception.hh"

#include <vector>

// constraint for making it a derivation of propertyinterface

template<class T, typename V = typename T::value_type>
class ArrayProperty: public PropertyInterface {
public:
  ArrayProperty() = delete;
  ArrayProperty(const std::string& _name, std::vector<V>& _value, int32_t _index=0)
    : PropertyInterface(SavePropertyType::ArrayProperty, _name, _index), c_value(_value),
      c_valuetypestr("") {
    c_value.clear();
    c_propdefs.clear();
  };
  virtual ~ArrayProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size) {
    _reader(c_valuetypestr).skip(1);

    Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    deserializeData(data);
  };

  virtual void deserializeData(Reader& _reader) {
    int32_t count;
    _reader(count);

    for (auto i=0; i<count; ++i) {
      c_value.emplace_back(V());
      c_propdefs.push_back(std::make_shared<T>(name(), c_value[i], i));
      c_propdefs[i]->deserializeData(_reader);
      //pd->deserializeData(_reader);
    }
  }

private:
  std::string c_valuetypestr;
  std::vector<std::shared_ptr<T> > c_propdefs;
  std::vector<V>& c_value;
};

#endif
