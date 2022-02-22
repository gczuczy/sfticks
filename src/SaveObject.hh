
#ifndef SFT_SAVEOBJECT_H
#define SFT_SAVEOBJECT_H
#include <string>

#include "Loader.hh"

class SaveObject {
public:
  SaveObject() = delete;
  SaveObject(Loader::Reader& _reader);
  virtual ~SaveObject()=0;

  inline std::string name() {return c_name;};
  inline std::string property_type() {return c_property_type;};
  inline std::string instance() {return c_instance;};

  virtual void debug() const;

protected:
  std::string c_name, c_property_type, c_instance;
};

#endif
