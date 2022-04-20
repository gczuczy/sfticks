
#ifndef SFT_STRUCTPROPERTY_H
#define SFT_STRUCTPROPERTY_H

#include "PropertyInterface.hh"
#include "SaveProperties.hh"

#include "Exception.hh"
#include "misc.hh"
#include "Trace.hh"

#include "SortRule.hh"
#include "InventoryStack.hh"
#include "SplinePointData.hh"
#include "FactoryCustomizationData.hh"
#include "Transform.hh"

#include <stdio.h>
#include <functional>
#include <typeinfo>

namespace FG {

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
    StructProperty(const std::string& _name, T& _value, int32_t _index=0, bool _debug=false) {
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
      _reader(strtype).skip(17);
      //printf("StructProperty size: %i\n type: '%s'\n", _size, strtype.c_str());
      //_reader.debug(16, "StructProperty");
      typecheck(strtype);

      Reader data(_reader, _size, __FILE__, __LINE__, __PRETTY_FUNCTION__);
      //data.dump("/tmp/struct-property-data.dump");
      deserializeData(data);
    }
    virtual void deserializeData(Reader& _reader) {
      //TRACE;
#if 0
      if ( typeid(T) == typeid(InventoryStack) ) {
	_reader.debug(16, "inventorystack").dump("/tmp/inventorystack.dump");
      }
      if ( typeid(T) == typeid(InventoryItem) ) {
	_reader.debug(16, "inventoryitem").dump("/tmp/inventoryitem.dump");
      }
#endif
      //printf("Parser(%s): %s\n", __PRETTY_FUNCTION__, c_parser?"yes":"no");
      if ( c_parser ) c_parser(std::ref(_reader));
      else loadProperties(_reader, c_debug);
      if ( c_debug ) printf("read struct %s: %s\n", name().c_str(), c_value.str().c_str());
    }

    static void deserializeNestedHeaders(Reader& _reader, NestedHeader& _nh) {
      _reader(_nh.name)(_nh.ptype)(_nh.size)(_nh.index)(_nh.strtype);
#if 0
      printf("nestedheaders\n: - name: %s\n - ptype: %s\n - size: %i\n - index: %i\n - strtype: %s\n",
	     _nh.name.c_str(), _nh.ptype.c_str(), _nh.size, _nh.index, _nh.strtype.c_str());
#endif
      int64_t skiplen = 17;
      if ( _nh.strtype == "Vector" ) {
	skiplen = 8;
      }
      _reader.skip(skiplen);
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
    std::function<void(Reader&)> c_parser;
    bool c_debug=false;
  };

  // specialization for GenericStruct
  template<>
  class StructProperty<std::string>: public PropertyInterface, public SaveProperties {
  public:
    typedef std::string value_type;
    StructProperty() = delete;
    virtual ~StructProperty()=default;
  protected:
    // For GenericStruct
    StructProperty(const std::string& _strtype, const std::string& _name, std::string& _value, int32_t _index=0)
      : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype(_strtype), c_value(_value) {
    }
  public:
    void typecheck(const std::string& _st) {
      if ( _st != c_strtype ) EXCEPTION(strprintf("StructProperty strtype mismatch: read:%s vs expected:%s",
						  _st.c_str(),
						  c_strtype.c_str()));
    }
    std::string c_strtype;
    std::string& c_value;
  };

  template<>
  StructProperty<SplitterSortRule>::StructProperty(const std::string& _name, SplitterSortRule& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<InventoryStack>::StructProperty(const std::string& _name, InventoryStack& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<InventoryItem>::StructProperty(const std::string& _name, InventoryItem& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<SplinePointData>::StructProperty(const std::string& _name, SplinePointData& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<Vector3>::StructProperty(const std::string& _name, Vector3& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<Quat>::StructProperty(const std::string& _name, Quat& _value, int32_t _index, bool _debug);

  template<>
  StructProperty<FactoryCustomizationData>::StructProperty(const std::string& _name, FactoryCustomizationData& _value,
							   int32_t _index, bool _debug);

  template<>
  StructProperty<Transform>::StructProperty(const std::string& _name, Transform& _value, int32_t _index, bool _debug);

}

#endif
