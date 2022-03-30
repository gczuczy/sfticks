
#ifndef SFT_STRUCTPROPERTY_H
#define SFT_STRUCTPROPERTY_H

#include "PropertyInterface.hh"

class StructProperty: public PropertyInterface {
public:
  StructProperty() = delete;
  StructProperty(const std::string& _strtype, const std::string& _name, int32_t _index=0);
  virtual ~StructProperty()=default;

  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader& _reader);

protected:
  void typecheck(const std::string& _st);

private:
  std::string c_strtype;
};

#endif
