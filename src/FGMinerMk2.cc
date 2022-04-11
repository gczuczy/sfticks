
#include "FGMinerMk2.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

namespace FG {

  std::string MinerMk2::objtypename("Build_MinerMk2_C");

  MinerMk2::MinerMk2(Reader& _reader, ObjectHeader& _fgoh)
    : Miner(EntityType::MinerMk2, _reader, _fgoh) {
    //defineInputs({"Input0"});
    //defineOutputs({"Output0"});
  }

  MinerMk2::~MinerMk2() {
  }

}
