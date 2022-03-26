
#ifndef SFT_FGOBJECTHEADER_H
#define SFT_FGOBJECTHEADER_H

#include "Saveable.hh"

#include <list>

class FGObjectHeader: public Saveable {
private:
  struct instdata {
    std::string str1; // namespace
    std::string str2; // :PersistentLevel
    std::string objtype;
    int32_t instid;
    // component data
    std::string compname;
    int32_t compinstid;
    void clear();
    void print();
  };
public:
  FGObjectHeader()=delete;
  FGObjectHeader(Reader& _reader);
  FGObjectHeader(const FGObjectHeader&)=default;
  virtual ~FGObjectHeader();

  inline bool isComponent() const {return c_objtype==0;};
  inline bool isEntity() const {return c_objtype==1;};
  inline std::string name() const {return c_name;};
  inline std::string proptype() const {return c_proptype;};
  inline std::string instance() const {return c_instance;};
  inline int32_t instanceid() const {return c_instanceid;};
  inline std::string FGObjectType() const {return c_fgobjtype;};

  virtual void deserializeProperties(Reader &_reader);
  virtual std::string str() const;
  // debug functions
  std::string str_compbase() const;

private:
  static bool parse_inststr(const std::string& _str, bool _entity, FGObjectHeader::instdata& _data);
  //static bool parse_inststr(const std::string& _str, bool _entity, instdata& _data);
  virtual void deserialize(Reader& _reader);

protected:
  void deserializeCompDefs(Reader& _reader);

protected:
  int32_t c_objtype;
  std::string c_name, c_proptype, c_instance;
  int32_t c_instanceid, c_component_instanceid;
  std::string c_fgobjtype;
  std::string c_component_name;

  objdef c_basecomp;
  std::list<objdef> c_compdefs;
};

#endif
