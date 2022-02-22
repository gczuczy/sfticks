
#ifndef SFT_SAVEOBJECT_H
#define SFT_SAVEOBJECT_H
#include <string>

#include "Loader.hh"

class SaveObject {
public:
  enum Type {
    Entity = 0,
    Component = 1
  };
  
  SaveObject() = delete;
  SaveObject(Loader::Reader& _reader);
  virtual ~SaveObject()=0;

  inline Type type() const {return c_type;};
  inline std::string name() const {return c_name;};
  inline std::string property_type() const {return c_property_type;};
  inline std::string instance() const {return c_instance;};

  virtual void debug();

protected:
  Type c_type;
  std::string c_name, c_property_type, c_instance;
};

#endif
