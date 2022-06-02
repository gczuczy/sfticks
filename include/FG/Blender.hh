
#ifndef SFT_FGBLENDER_H
#define SFT_FGBLENDER_H

#include "FG/IOUnit.hh"

namespace FG {

  class Blender: public IOUnit {
  public:
    Blender()=delete;
    Blender(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~Blender();

    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
