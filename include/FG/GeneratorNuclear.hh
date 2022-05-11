
#ifndef SFT_FGGENERATORNUCLEAR_H
#define SFT_FGGENERATORNUCLEAR_H

#include "FG/GeneratorUnit.hh"

namespace FG {

  class GeneratorNuclear: public GeneratorUnit {
  public:
    GeneratorNuclear()=delete;
    GeneratorNuclear(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~GeneratorNuclear();

    static std::string objtypename;

    inline int32_t mWasteLeftFromCurrentFuel() const {return c_mWasteLeftFromCurrentFuel;};
    inline float mCurrentSupplementalAmount() const {return c_mCurrentSupplementalAmount;};
    inline bool mHasSupplementalCached() const {return c_mHasSupplementalCached;};

  private:
    int32_t c_mWasteLeftFromCurrentFuel;
    float c_mCurrentSupplementalAmount;
    bool c_mHasSupplementalCached;
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
