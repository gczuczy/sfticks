
#include "FGBlender.hh"

namespace FG {

  std::string Blender::objtypename("Build_Blender_C");

  Blender::Blender(Reader& _reader, ObjectHeader& _fgoh)
    : IOUnit(EntityType::Blender, _reader, _fgoh){
  }

  Blender::~Blender() {
  }

}
