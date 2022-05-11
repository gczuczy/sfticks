
#ifndef SFT_FACTORYCUSTOMIZATIONDATA_H
#define SFT_FACTORYCUSTOMIZATIONDATA_H

#include "FG/ObjectReference.hh"

namespace FG {

  struct FactoryCustomizationData {
    ObjectReference SwatchDesc;
    inline std::string str() {
      return SwatchDesc.str();
    }
  };
}

#endif
