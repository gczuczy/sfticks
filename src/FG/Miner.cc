
#include "FG/Miner.hh"

#include "FG/FloatProperty.hh"
#include "FG/ObjectProperty.hh"

namespace FG {

  Miner::Miner(EntityType _et, Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(_et, _reader, _fgoh) {
    defineProperty(std::make_shared<FloatProperty>("mExtractStartupTimer", c_mExtractStartupTimer));
    defineProperty(std::make_shared<FloatProperty>("mCurrentExtractProgress", c_mCurrentExtractProgress));
    defineProperty(std::make_shared<ObjectProperty>("mExtractableResource", c_mExtractableResource));
  }

  Miner::~Miner() {
  }

}
