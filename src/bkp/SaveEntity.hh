
#ifndef SFT_SAVEENTITY_H
#define SFT_SAVEENTITY_H

#include <list>
#include <memory>

#include "SaveObject.hh"
#include "ObjectReference.hh"
#include "vectors.hh"

class SaveEntity: public SaveObject {
public:
  SaveEntity(Reader& _reader);
  virtual ~SaveEntity();

  virtual void debug();

  virtual SaveObject& loadProperties(Reader &_reader);

  inline const std::string& parentObjectRoot() const {return c_parent_object_root;};
  inline const std::string& parentObjectName() const {return c_parent_object_name;};

private:
  int32_t c_needtransform;
  Vector4 c_rotation;
  Vector3 c_position, c_scale;
  int32_t c_placedinlevel;
  std::string c_parent_object_root;
  std::string c_parent_object_name;
  std::list<std::shared_ptr<ObjectReference> > c_components;
};

#endif
