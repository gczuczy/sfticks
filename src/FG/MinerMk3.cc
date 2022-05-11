
#include "FG/MinerMk3.hh"
#include "SFT/Exception.hh"
#include "SFT/Trace.hh"

#include <cassert>

namespace FG {

  std::string MinerMk3::objtypename("Build_MinerMk3_C");

  MinerMk3::MinerMk3(Reader& _reader, ObjectHeader& _fgoh)
    : Miner(EntityType::MinerMk3, _reader, _fgoh) {
    //defineInputs({"Input0"});
    //defineOutputs({"Output0"});
  }

  MinerMk3::~MinerMk3() {
  }

}
