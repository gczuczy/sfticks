
#include "FGConstructorMk1.hh"
#include "Exception.hh"
#include "Trace.hh"

#include <cassert>

FGConstructorMk1::FGConstructorMk1(Reader& _reader, FGObjectHeader& _fgoh)
  : FGIOUnit(FGEntityType::ConstructorMk1, _reader, _fgoh){
  defineProperty("mCurrentManufacturingProgress", "FloatProperty",
		 [&](Reader& _r, int32_t)->void{
		   TRACE;
		   _reader(c_mCurrentManufacturingProgress);
		   _reader.debug(4, "Constr-CMP");
		 });
}

FGConstructorMk1::~FGConstructorMk1() {
}
