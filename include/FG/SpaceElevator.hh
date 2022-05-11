
#ifndef SFT_FGSPACEELEVATOR_H
#define SFT_FGSPACEELEVATOR_H

#include "FG/IOUnit.hh"

namespace FG {

  class SpaceElevator: public IOUnit {
  public:
    SpaceElevator()=delete;
    SpaceElevator(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~SpaceElevator();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
