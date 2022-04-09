
#include "FGBlender.hh"

std::string FGBlender::objtypename("Build_Blender_C");

FGBlender::FGBlender(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::Blender, _reader, _fgoh){
}

FGBlender::~FGBlender() {
}

