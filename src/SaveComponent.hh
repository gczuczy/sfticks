
#ifndef SFT_SAVECOMPONENT_H
#define SFT_SAVECOMPONENT_H

#include "SaveObject.hh"

class SaveComponent: public SaveObject {
public:
  SaveComponent(Loader::Reader& _reader);
  virtual ~SaveComponent();

  virtual void debug();
private:
  std::string c_parent_entity_name;
};

#endif
