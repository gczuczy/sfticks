
#ifndef SFT_FGGENERICENTITY_H
#define SFT_FGGENERICENTITY_H

#include "FG/Entity.hh"

namespace FG {

  class GenericEntity: public Entity {
  public:
    GenericEntity()=delete;
    GenericEntity(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GenericEntity();

    virtual void deserializeProperties(Reader &_reader);

  private:
    virtual void deserialize(Reader &_reader);

  private:
    std::string c_properties;
  };

}

#endif
