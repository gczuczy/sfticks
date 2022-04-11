
#include "FGMinerMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

namespace FG {

  std::string MinerMk1::objtypename("Build_MinerMk1_C");

  MinerMk1::MinerMk1(Reader& _reader, ObjectHeader& _fgoh)
    : Miner(EntityType::MinerMk1, _reader, _fgoh) {
  }

  MinerMk1::~MinerMk1() {
  }

}
