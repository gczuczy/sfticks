
#ifndef SFT_MAPPROPERTY_HH
#define SFT_MAPPROPERTY_HH

#include "PropertyInterface.hh"
#include "Exception.hh"
#include "Trace.hh"

//#include <list>
#include <map>

template<class Key, class T>
class MapProperty: public PropertyInterface {
public:
  typedef std::map<typename Key::value_type, typename T::value_type> value_type;
  MapProperty() = delete;
  MapProperty(const std::string& _name, value_type& _value, int32_t _index=0)
    : PropertyInterface(SavePropertyType::MapProperty, _name, _index), c_value(_value),
      c_keytypestr(""), c_valuetypestr("") {
    c_value.clear();
    //c_propdefs.clear();
  };
  virtual ~MapProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size) {
    //TRACE;
    _reader(c_keytypestr)(c_valuetypestr).skip(1);

    //_reader.debug(16, "map-outer").dump("/tmp/map-outer.dump");
    Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    //data.debug(16, "map-inner").dump("/tmp/map-inner.dump");
    deserializeData(data);
  };

  virtual void deserializeData(Reader& _reader) {
    //TRACE;
    int32_t count;
    _reader.skip(4)(count);
    //_reader.debug(16, "map-data").dump("/tmp/map-data.dump");
    //EXCEPTION("e!");
    for (auto i=0; i<count; ++i) {
      typename Key::value_type key;
      typename T::value_type value;
      Key keyprop("", key);
      T valprop("", value);

      keyprop.deserializeData(_reader);
      valprop.deserializeData(_reader);
      c_value[key] = value;
    }
  }

private:
  std::string c_keytypestr, c_valuetypestr;
  //std::list<std::pair<Key, T> > c_propdefs;
  value_type& c_value;
};

#endif
