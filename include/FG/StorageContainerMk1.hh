
#ifndef SFT_FGSTORAGECONTAINERMK1_H
#define SFT_FGSTORAGECONTAINERMK1_H

#include "FG/StorageUnit.hh"

namespace FG {

  class StorageContainerMk1: public StorageUnit {
  public:
    StorageContainerMk1()=delete;
    StorageContainerMk1(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~StorageContainerMk1();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
