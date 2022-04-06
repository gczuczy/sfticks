
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

