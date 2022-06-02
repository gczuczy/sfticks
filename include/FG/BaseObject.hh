
#ifndef SFT_FGBASEOBJECT_H
#define SFT_FGBASEOBJECT_H

#include <stdint.h>
#include <memory>

namespace FG {

  enum class ObjectType:uint8_t {
    ENTITY=0,
    COMPONENT,
    DESC,
    RECIPE,
  };

  class BaseObject {
  public:
    BaseObject()=delete;
    virtual ~BaseObject()=0;
  protected:
    BaseObject(ObjectType _ot);

  public:
    inline ObjectType objectType() const {return c_objtype;};

  private:
    ObjectType c_objtype;
  };
  typedef std::shared_ptr<BaseObject> BaseObjectSP;
}

#endif
