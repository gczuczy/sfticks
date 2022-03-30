
#ifndef SFT_OBJECTPROPERTY_H
#define SFT_OBJECTPROPERTY_H

#include "PropertyInterface.hh"
#include "ObjectReference.hh"

class ObjectProperty: public PropertyInterface {
public:
  ObjectProperty() = delete;
  ObjectProperty(const std::string& _name, ObjectReference& _value, int32_t _index=0);
  virtual ~ObjectProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader& _reader);

private:
  ObjectReference& c_value;
};

#endif
