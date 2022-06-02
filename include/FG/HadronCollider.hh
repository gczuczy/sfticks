
#ifndef SFT_FGHADRONCOLLIDER_H
#define SFT_FGHADRONCOLLIDER_H

#include "FG/IOUnit.hh"

namespace FG {

  class HadronCollider: public IOUnit {
  public:
    HadronCollider()=delete;
    HadronCollider(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~HadronCollider();
    
    virtual void doTick(SFT::tickinfo_t& _tick);

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
