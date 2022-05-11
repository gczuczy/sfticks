
#ifndef SFT_ARRAYPROPERTY_HH
#define SFT_ARRAYPROPERTY_HH

#include "FG/PropertyInterface.hh"
#include "SFT/Exception.hh"
#include "SFT/Trace.hh"
#include "misc.hh"

#include <vector>

namespace FG {

  template<class T, typename V = typename T::value_type>
  class ArrayProperty: public PropertyInterface {
  public:
    ArrayProperty() = delete;
    ArrayProperty(const std::string& _name, std::vector<V>& _value, int32_t _index=0, bool _debug=false)
      : PropertyInterface(SavePropertyType::ArrayProperty, _name, _index), c_value(_value),
	c_valuetypestr(""), c_debug(_debug) {
      c_value.clear();
      c_propdefs.clear();
    };
    virtual ~ArrayProperty()=default;

    virtual void deserialize(Reader& _reader, int32_t _size) {
      //TRACE;
      _reader(c_valuetypestr).skip(1);

      //_reader.debug(32,"array-outer").dump("/tmp/array-outer.dump");
      Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
      deserializeData(data);
    };

    virtual void deserializeData(Reader& _reader) {
      //TRACE;
      int32_t count;
      _reader(count);
      //_reader.debug(16, "array-data").dump("/tmp/array-data.dump");

      static int x=0;
      if ( c_debug ) {
	++x;
	printf("ArrayProperty<%s>(%s) %i items:\n", typeid(T).name(),
	       name().c_str(), count);
	std::string str = strprintf("/tmp/array-debug-%i.dump", x);
	_reader.debug(4, str).dump(str);
      }
      T::deserializeNestedHeaders(_reader, c_nestedheaders);
      for (auto i=0; i<count; ++i) {
#if 0
	if ( c_debug ) {
	  printf(" - Reading %i/%i\n", i, count);
	  _reader.debug(4, strprintf("array-debug-%i %i/%i", x, i, count));
	}
#endif
	c_value.emplace_back(V());
	T def(name(), c_value[i], i, c_debug);
	def.deserializeData(_reader);
	
	//c_propdefs.push_back(std::make_shared<T>(name(), c_value[i], 0, c_debug));
	//c_propdefs[i]->deserializeData(_reader);
      }
      //if ( c_debug ) EXCEPTION("lofasz");
    }

  private:
    std::string c_valuetypestr;
    std::vector<std::shared_ptr<T> > c_propdefs;
    std::vector<V>& c_value;
    bool c_debug = false;
    typename T::NestedHeader c_nestedheaders;
  };

}

#endif
