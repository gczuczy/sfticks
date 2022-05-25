
#include "FG/MinerMk2.hh"
#include "SFT/Exception.hh"
#include "SFT/Trace.hh"

#include <cassert>

namespace FG {

  std::string MinerMk2::objtypename("Build_MinerMk2_C");

  MinerMk2::MinerMk2(Reader& _reader, ObjectHeader& _fgoh)
    : Miner(EntityType::MinerMk2, _reader, _fgoh) {
  }

  MinerMk2::~MinerMk2() {
  }

}
