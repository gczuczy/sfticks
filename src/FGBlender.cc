
#include "FGBlender.hh"

FGBlender::FGBlender(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::Blender, _reader, _fgoh){
}

FGBlender::~FGBlender() {
}

