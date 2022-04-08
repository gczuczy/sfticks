
#include "StructProperty.hh"

#include "ObjectProperty.hh"
#include "IntProperty.hh"

template<>
StructProperty<SplitterSortRule>::StructProperty(const std::string& _name, SplitterSortRule& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("SplitterSortRule"), c_value(_value) {
  //TRACE;
  defineProperty(std::make_shared<ObjectProperty>("ItemClass", c_value.ItemClass));
  defineProperty(std::make_shared<IntProperty>("OutputIndex", c_value.OutputIndex));
}

template<>
StructProperty<InventoryStack>::StructProperty(const std::string& _name, InventoryStack& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("InventoryStack"), c_value(_value) {
  //TRACE;
  defineProperty(std::make_shared<StructProperty<InventoryItem> >("Item", c_value.Item));
  defineProperty(std::make_shared<IntProperty>("NumItems", c_value.NumItems));
}

template<>
StructProperty<InventoryItem>::StructProperty(const std::string& _name, InventoryItem& _value, int32_t _index)
  : PropertyInterface(SavePropertyType::StructProperty, _name, _index), c_strtype("InventoryItem"), c_value(_value) {
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

