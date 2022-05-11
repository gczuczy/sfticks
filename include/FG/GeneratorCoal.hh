
#ifndef SFT_FGGENERATORCOAL_H
#define SFT_FGGENERATORCOAL_H

#include "FG/GeneratorUnit.hh"

namespace FG {

  class GeneratorCoal: public GeneratorUnit {
  public:
    GeneratorCoal()=delete;
    GeneratorCoal(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GeneratorCoal();

    inline float& mCurrentSupplementalAmount() {return c_mCurrentSupplementalAmount;};
    inline bool& mHasSupplementalCached() {return c_mHasSupplementalCached;};

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
    float c_mCurrentSupplementalAmount;
    bool c_mHasSupplementalCached;
  };

}

#endif
