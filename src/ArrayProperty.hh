
#ifndef SFT_ARRAYPROPERTY_HH
#define SFT_ARRAYPROPERTY_HH

#include "PropertyInterface.hh"
#include "Exception.hh"
#include "StructProperty.hh"
#include "Trace.hh"

#include <vector>

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
    //TRACE;
    _reader(c_valuetypestr).skip(1);

    _reader.debug(32,"array-outer").dump("/tmp/array-outer.dump");
    Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    deserializeData(data);
  };

  virtual void deserializeData(Reader& _reader) {
    //TRACE;
    int32_t count;
    _reader(count);
    T::deserializeNestedHeaders(_reader, c_nestedheaders);
    _reader.debug(16, "array-data").dump("/tmp/array-data.dump");

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
  typename T::NestedHeader c_nestedheaders;
};


#endif