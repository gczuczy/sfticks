
#ifndef SFT_FGCOMPONENT_H
#define SFT_FGCOMPONENT_H

#include "FGObjectHeader.hh"

#include <stdint.h>
#include <string>
#include <memory>

#include "vectors.hh"
#include "misc.hh"

class FGComponent: public FGObjectHeader {
  FGComponent()=delete;
public:
  FGComponent(Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGComponent();

  inline std::string parentEntityName() const {return c_parent_entity_name;};
  inline std::string instanceName() const {return strprintf("%s_%i", c_component_name.c_str(), c_component_instanceid);};

private:
  virtual void deserialize(Reader &_reader);

protected:
  std::string c_parent_entity_name;
};

typedef std::shared_ptr<FGComponent> FGComponentSP;

#endif
