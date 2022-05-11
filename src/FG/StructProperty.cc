
#include "FG/StructProperty.hh"
#include "SFT/Trace.hh"

#include "FG/ObjectProperty.hh"
#include "FG/IntProperty.hh"

namespace FG {

  template<>
  StructProperty<SplitterSortRule>::StructProperty(const std::string& _name, SplitterSortRule& _value,
						   int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("SplitterSortRule"),
      c_value(_value), c_debug(_debug) {
    //TRACE;
    defineProperty(std::make_shared<ObjectProperty>("ItemClass", c_value.ItemClass));
    defineProperty(std::make_shared<IntProperty>("OutputIndex", c_value.OutputIndex));
  }

  template<>
  StructProperty<InventoryStack>::StructProperty(const std::string& _name, InventoryStack& _value,
						 int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("InventoryStack"),
      c_value(_value), c_debug(_debug) {
    //TRACE;
    defineProperty(std::make_shared<StructProperty<InventoryItem> >("Item", c_value.Item));
    defineProperty(std::make_shared<IntProperty>("NumItems", c_value.NumItems));
  }

  template<>
  StructProperty<InventoryItem>::StructProperty(const std::string& _name, InventoryItem& _value,
						int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("InventoryItem"),
      c_value(_value), c_debug(_debug) {
    //TRACE;
    //defineProperty(std::make_shared<StructProperty<InventoryItem> >("Item", c_value.Item));
    c_parser = [&](Reader& _r)->void {
#if 0
      TRACE;
      t.detail("reader id", _r.id())
	.detail("reader pos", _r.pos())
	.detail("reader len", _r.len());
      //t.debug();
#endif
      _r(c_value.un1)(c_value.ItemType)(c_value.un2)(c_value.un3);
#if 0
      printf("un1: %i\nItemType: %s\nun2: %s\nun3: %s\n",
	     c_value.un1, c_value.ItemType.c_str(), c_value.un2.c_str(), c_value.un3.c_str());
#endif
    };
  }

  template<>
  StructProperty<SplinePointData>::StructProperty(const std::string& _name, SplinePointData& _value,
						  int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("SplinePointData"),
      c_value(_value), c_debug(_debug) {
    defineProperty(std::make_shared<StructProperty<Vector3> >("Location", c_value.Location));
    defineProperty(std::make_shared<StructProperty<Vector3> >("ArriveTangent", c_value.ArriveTangent));
    defineProperty(std::make_shared<StructProperty<Vector3> >("LeaveTangent", c_value.LeaveTangent));
  }

  template<>
  StructProperty<Vector3>::StructProperty(const std::string& _name, Vector3& _value,
					  int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("Vector"),
      c_value(_value), c_debug(_debug) {
    c_parser = [&](Reader& _r)->void {
      //TRACE;
      _r(c_value);
    };
  }

  template<>
  StructProperty<Quat>::StructProperty(const std::string& _name, Quat& _value, int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("Quat"),
      c_value(_value), c_debug(_debug) {
    c_parser = [&](Reader& _r)->void {
      _r(c_value);
    };
  }

  template<>
  StructProperty<FactoryCustomizationData>::StructProperty(const std::string& _name, FactoryCustomizationData& _value,
							   int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("FactoryCustomizationData"),
      c_value(_value), c_debug(_debug) {
    defineProperty(std::make_shared<ObjectProperty>("SwatchDesc", c_value.SwatchDesc));
  }

  template<>
  StructProperty<Transform>::StructProperty(const std::string& _name, Transform& _value, int32_t _index, bool _debug)
    : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("Transform"),
      c_value(_value), c_debug(_debug) {
    defineProperty(std::make_shared<StructProperty<Quat> >("Rotation", c_value.Rotation));
    defineProperty(std::make_shared<StructProperty<Vector3> >("Translation", c_value.Translation));
  }
}
