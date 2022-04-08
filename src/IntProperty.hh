
#ifndef SFT_INTPROPERTY_H
#define SFT_INTPROPERTY_H

#include "PropertyInterface.hh"

class IntProperty: public PropertyInterface {
public:
  struct NestedHeader {
  };
public:
  typedef int32_t value_type;
  IntProperty() = delete;
  IntProperty(const std::string& _name, int32_t& _value, int32_t _index=0);
  virtual ~IntProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader& _reader);

  static void deserializeNestedHeaders(Reader& _reader, NestedHeader& _nh);

private:
  int32_t& c_value;
};

#endif
