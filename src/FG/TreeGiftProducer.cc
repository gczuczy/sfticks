
#include "FG/TreeGiftProducer.hh"
#include "SFT/Exception.hh"
#include "SFT/Trace.hh"

#include <cassert>

namespace FG {

  std::string TreeGiftProducer::objtypename("Build_TreeGiftProducer_C");

  TreeGiftProducer::TreeGiftProducer(Reader& _reader, ObjectHeader& _fgoh)
    : Miner(EntityType::TreeGiftProducer, _reader, _fgoh) {
  }

  TreeGiftProducer::~TreeGiftProducer() {
  }

}
