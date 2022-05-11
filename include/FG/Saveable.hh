
#ifndef SFT_SAVEABLE_H
#define SFT_SAVEABLE_H

#include "SFT/Reader.hh"

#include <string>
#include <memory>
#include <map>

#include "FG/SaveProperties.hh"

namespace FG {

  class Saveable: public SaveProperties {
  protected:
  public:
    Saveable();
    virtual ~Saveable()=0;

  public:
    virtual void deserialize(Reader& _reader)=0;
    virtual void deserializeProperties(Reader& _reader)=0;
    virtual std::string str() const=0;
  };

  typedef std::shared_ptr<Saveable> SaveableSP;

}

#endif
