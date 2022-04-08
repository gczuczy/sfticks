
#ifndef SFT_FGCOMPONENT_H
#define SFT_FGCOMPONENT_H

#include "FGObjectHeader.hh"

#include <stdint.h>
#include <string>
#include <memory>

#include "vectors.hh"
#include "misc.hh"

enum class FGComponentType: int32_t {
  Generic=-1,
  InOutPort=0,
};

class FGComponent: public FGObjectHeader {
  FGComponent()=delete;
public:
  FGComponent(FGComponentType _comptype, Reader& _reader, FGObjectHeader& _fgoh);
  virtual ~FGComponent();

  inline FGComponentType componentType() const {return c_comptype;};
  inline std::string parentEntityName() const {return c_parent_entity_name;};
  inline std::string instanceName() const {return strprintf("%s_%i", c_component_name.c_str(), c_component_instanceid);};

  virtual void deserializeProperties(Reader &_reader);
private:
  virtual void deserialize(Reader &_reader);

protected:
  std::string c_parent_entity_name;

private:
  FGComponentType c_comptype;
};

typedef std::shared_ptr<FGComponent> FGComponentSP;

#endif
