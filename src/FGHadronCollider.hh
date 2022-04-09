
#ifndef SFT_FGHADRONCOLLIDER_H
#define SFT_FGHADRONCOLLIDER_H

#include "FGIOUnit.hh"

namespace FG {

  class HadronCollider: public IOUnit {
  public:
    HadronCollider()=delete;
    HadronCollider(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~HadronCollider();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
