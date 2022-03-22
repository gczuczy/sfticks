
#ifndef SFT_SAVEWORLD_H
#define  SFT_SAVEWORLD_H

#include <vector>
#include <memory>

#include "SaveObject.hh"

class SaveWorld {
public:
  SaveWorld();
  SaveWorld(const SaveWorld&) = delete;
  ~SaveWorld();

  SaveWorld& add(std::shared_ptr<SaveObject>& _obj);
  inline int objcount() const {return c_objects.size();};
  inline std::shared_ptr<SaveObject> operator[](int _idx) {return c_objects[_idx];};

private:
  std::vector<std::shared_ptr<SaveObject> > c_objects;
};

#endif
