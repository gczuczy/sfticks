
#include "SaveWorld.hh"

SaveWorld::SaveWorld() {
}

SaveWorld::~SaveWorld() {
}

SaveWorld& SaveWorld::add(std::shared_ptr<SaveObject>& _obj) {
  c_objects.push_back(_obj);
  return *this;
}
