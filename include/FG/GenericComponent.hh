
#ifndef FST_FGGENERICCOMPONENT_H
#define FST_FGGENERICCOMPONENT_H

#include "FG/Component.hh"

namespace FG {

  class GenericComponent: public Component {
  public:
    GenericComponent()=delete;
    GenericComponent(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GenericComponent();

    virtual void deserializeProperties(Reader &_reader);

    // debug functions
    void dump(const std::string _file);
    virtual std::string compdetails();

  private:
    virtual void deserialize(Reader &_reader);

  private:
    std::string c_properties;
  };

}

#endif
