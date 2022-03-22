
#include "StructProperty.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <set>

StructProperty::Header::Header(Reader &_r, std::string _name, int32_t _index, bool _nested)
  : SaveProperty::Header(PropertyType::StructProperty, _r, _name, _index) {
  TRACE;
  t.detail("name", c_name)
    .detail("type", c_ptype)
    .detail("index", c_index)
    .detail("nested", _nested?"yes":"no")
    .detail("reader", _r.id())
    .detail("readerpos", _r.pos())
    .detail("readerlen", _r.len());
  _r.debug(128, "StructProperty::Header::Header start");
  if ( _nested ) {
    _r(c_len).skip(4)(c_struct_type);
  } else {
    _r.skip(4+4+1)(c_struct_type);
  }
  t.detail("datalen", c_len);
  t.detail("structtype", c_struct_type);
  t.debug();
};

StructProperty::Header::Header(std::string _strtype, std::string _name, int32_t _index)
  : SaveProperty::Header(PropertyType::StructProperty, _name, _index), c_struct_type(_strtype) {
  TRACE;
  t.detail("name", c_name)
    .detail("type", c_ptype)
    .detail("index", c_index)
    .detail("structtype", c_struct_type);
}

StructProperty::Header::~Header() {
}

StructProperty::StructProperty(std::shared_ptr<Header> _header, Reader& _reader)
  : SaveProperty(_header){
  TRACE;
  c_struct_type = _header->structtype();
  t.detail("name", c_name)
    .detail("reader", _reader.id())
    .detail("type", c_type)
    .detail("index", c_index)
    .detail("readerpos", _reader.pos())
    .detail("readerlen", _reader.len())
    .detail("structtype", c_struct_type);
  parse(_reader);
}

StructProperty::~StructProperty() {
}

void StructProperty::parse(Reader& _reader) {

  TRACE;
  t.detail("reader", _reader.id())
    .detail("reader", _reader.id())
    .detail("name", c_name);
  t.printf("Parsing StructProperty %s\n Type: %s\n\n", c_name.c_str(), c_struct_type.c_str());

  if ( c_struct_type == "Box" ) {
    _reader(c_box_min)(c_box_max).skip(1);
#ifdef SFT_DEBUG
    t.printf("Parsed StructProperty/Box %s:\n Min: %s\n Max: %s\n",
	   c_name.c_str(), c_box_min.str().c_str(), c_box_max.str().c_str());
#endif
  } else if ( c_struct_type == "Quat" ) {
    _reader(c_quat);
#ifdef SFT_DEBUG
    t.printf("Parsed StructProperty/Quat %s:\n Quat: %s\n",
	   c_name.c_str(), c_quat.str().c_str());
#endif
  } else if ( c_struct_type == "LinearColor" ) {
    _reader(c_quat);
#ifdef SFT_DEBUG
    t.printf("Parsed StructProperty/Quat %s:\n Quat: %s\n",
	   c_name.c_str(), c_quat.str().c_str());
#endif
  } else if ( c_struct_type == "Vector" ) {
    _reader(c_vector);
#ifdef SFT_DEBUG
    t.printf("Parsed StructProperty/Vector %s:\n Quat: %s\n",
	   c_name.c_str(), c_vector.str().c_str());
#endif
  } else if ( c_struct_type == "InventoryItem" ) {
    /*
    t.printf("Parsing StructProperty/InventoryItem %s\n", c_name.c_str());
    _reader.dump("/tmp/struct.inventoryitem.dump").debug(128, "Inventoryitem");
    */

    std::string name;
    _reader.skip(4)(name).skip(8);
    t.detail("InItname", name);

    try {
      c_members[name] = factory(_reader);
    }
    catch (Exception &e) {
      t.debug();
      throw e;
    }
    
#ifdef SFT_DEBUG
    t.printf("Parsed StructProperty/InventoryItem %s:\n item: %s\n",
	   c_name.c_str(), name.c_str());
#endif
  } else {
#if 1
    std::set<std::string> known{"TimeTableStop", "TrainDockingRuleSet", "RemovedInstanceArray", "RemovedInstance",
      "Transform", "FactoryCustomizationData", "SpawnData", "TrainSimulationData", "mActorsBuiltCount", "InventoryStack",
      "LightSourceControlData", "SplinePointData"};
    // this is the generic struct parsing
#ifdef SFT_DEBUG
    t.printf("GENERIC StructProperty type: %s\n", c_struct_type.c_str());
#endif
    if ( !known.contains(c_struct_type) ) {
      _reader.dump("/tmp/struct.generic.dump").debug(128, "struct generic");
      /*
      Reader sdata(_reader, _size, __FILE__, __LINE__,  "StructProperty::parse/generic");
      sdata.dump("/tmp/struct.internal.dump").debug(128, "struct internal");
      */
      EXCEPTION(std::string("Generic Struct property, unknown type: ")+c_struct_type);
    }
#endif
    std::shared_ptr<SaveProperty> obj;
    _reader.debug(32, "struct-generic").dump("/tmp/struct-generic.dump");
    try {
      while ( !_reader.eof() && (obj = SaveProperty::factory(_reader)) ) {
	t.printf("  Struct member: %s/%i\n", obj->name().c_str(), obj->index());
	c_members[obj->name()] = obj;
	_reader.debug(32, "struct-generic-after");
      }
    }
    catch (Exception &e) {
      printf("!!! - START -  Struct-Generic exception: %s\n", e.what());
      _reader.debug(32, "struct-generic-e").dump("/tmp/struct-generic-e.dump");
      t.debug();
      printf("!!! - END - Struct-Generic exception: %s\n", e.what());
      throw e;
    }
    _reader.debug(32, "struct-generic-end");
  }
#ifdef SFT_DEBUG
  t.printf("Loaded StructProperty %s\n", c_name.c_str());
#endif
}

