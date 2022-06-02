
#include "FG/Blender.hh"
#include "SFT/Exception.hh"
#include "misc.hh"

namespace FG {

  std::string Blender::objtypename("Build_Blender_C");

  Blender::Blender(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Blender, _reader, _fgoh){
  }

  Blender::~Blender() {
  }

  void Blender::doTick(SFT::tickinfo_t& _tick) {
    EXCEPTION(strprintf("Check %s", __PRETTY_FUNCTION__));
  }
  
}
