
#ifndef SFT_SAVEENTITY_H
#define SFT_SAVEENTITY_H

#include "SaveObject.hh"
#include "vectors.hh"

class SaveEntity: public SaveObject {
public:
  SaveEntity(Loader::Reader& _reader);
  virtual ~SaveEntity();

  virtual void debug();
private:
  int32_t c_needtransform;
  Vector4 c_rotation;
  Vector3 c_position, c_scale;
  int32_t c_placedinlevel;
};

#endif
