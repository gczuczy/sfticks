
#ifndef SFT_PROPERTYINTERFACE_H
#define SFT_PROPERTYINTERFACE_H

#include <stdint.h>

#include <string>
#include <memory>

#include "Reader.hh"
#include "SavePropertyType.hh"

class PropertyInterface {
public:
  PropertyInterface()=delete;
  PropertyInterface(SavePropertyType _pt, const std::string& _name, int32_t _index);
  virtual ~PropertyInterface()=default;

  // it's separated, first should call the second at the end
  // in nested structures there are no headers, just data in the direct buffer,
  // the name,type,size,index provided by other means
  // NOTE for now these have exception-throwing implementations for development purposes
  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader&);

  inline SavePropertyType savePropertyType() const {return c_pt;};
  inline std::string savePropertyTypeStr() const {return ptypestr(c_pt);};
  inline std::string name() const {return c_name;};
  inline int32_t index() const {return c_index;};

private:
  SavePropertyType c_pt;
  std::string c_name;
  int32_t c_index;
};
typedef std::shared_ptr<PropertyInterface> PropertyInterfaceSP;

#endif

