
#ifndef SFT_FGSTORAGECONTAINERMK2_H
#define SFT_FGSTORAGECONTAINERMK2_H

#include "FG/StorageUnit.hh"

namespace FG {

  class StorageContainerMk2: public StorageUnit {
  public:
    StorageContainerMk2()=delete;
    StorageContainerMk2(Reader& _reader, ObjectHeader& _fgoh);
    virtual ~StorageContainerMk2();

    static std::string objtypename;

  private:
    //virtual void deserialize(Reader &_reader);
  };

}

#endif
