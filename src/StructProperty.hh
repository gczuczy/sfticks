
#ifndef SFT_STRUCTPROPERTY_H
#define SFT_STRUCTPROPERTY_H

#include "PropertyInterface.hh"
#include "SaveProperties.hh"

#include "Exception.hh"
#include "misc.hh"
#include "SortRule.hh"
#include "Trace.hh"

#include <type_traits>

template<class T>
class StructProperty: public PropertyInterface, public SaveProperties {
public:
  struct NestedHeader {
    std::string name;
    std::string ptype;
    int32_t size;
    int32_t index;
    std::string strtype;
  };
  typedef T value_type;
  StructProperty() = delete;
  StructProperty(const std::string& _name, T& _value, int32_t _index=0) {
    EXCEPTION("Unimplemented StructProperty");
  }
  virtual ~StructProperty()=default;
protected:
  // For GenericStruct
  StructProperty(const std::string& _strtype, const std::string& _name, T& _value, int32_t _index=0)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype(_strtype), c_value(_value) {
  }

public:
  virtual void deserialize(Reader& _reader, int32_t _size) {
    //TRACE;
    std::string strtype;
    _reader(strtype);
    //printf("StructProperty size: %i\n type: '%s'\n", _size, strtype.c_str());
    _reader.debug(16, "StructProperty");
    typecheck(strtype);

    Reader data(_reader, _size);
    //data.dump("/tmp/struct-property-data.dump");
    deserializeData(data);
  }
  virtual void deserializeData(Reader& _reader) {
    //TRACE;
    loadProperties(_reader);
  }

  static void deserializeNestedHeaders(Reader& _reader, NestedHeader& _nh) {
    _reader(_nh.name)(_nh.ptype)(_nh.size)(_nh.index)(_nh.strtype).skip(17);
  };

protected:
  void typecheck(const std::string& _st) {
    if ( _st != c_strtype ) EXCEPTION(strprintf("StructProperty strtype mismatch: read:%s vs expected:%s",
						_st.c_str(),
						c_strtype.c_str()));
  }

private:
  std::string c_strtype;
  T& c_value;
};

template<>
StructProperty<SplitterSortRule>::StructProperty(const std::string& _name, SplitterSortRule& _value, int32_t _index);

#endif
