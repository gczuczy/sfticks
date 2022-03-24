
#include "FGResourceSink.hh"

FGResourceSink::FGResourceSink(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ResourceSink, _reader, _fgoh){
}

FGResourceSink::~FGResourceSink() {
}

