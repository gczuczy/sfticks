
#ifndef SFT_SAVEABLE_H
#define SFT_SAVEABLE_H

#include "Reader.hh"

#include <string>
#include <memory>
#include <functional>
#include <set>
#include <map>

#include "PropertyInterface.hh"

class Saveable {
protected:
  struct objdef {
    objdef() = default;
    objdef(std::string _ns, std::string _compname);
    objdef(const objdef&) = default;
    objdef(objdef&& other);
    objdef(Reader& _r);
    objdef& operator=(const objdef& other)=default;
    std::string ns;
    std::string compname;
  };
  typedef std::function<void(Reader&, int32_t)> prophfn_t;
private:
  struct prophdef {
    prophdef() = default;
    prophdef(std::string _pn, std::string _pt, prophfn_t _h);
    prophdef(const prophdef&) = default;
    prophdef(prophdef&& other);
    prophdef& operator=(const prophdef& other)=default;
    std::string propname;
    std::string proptype;
    prophfn_t handler;
  };
public:
  Saveable();
  virtual ~Saveable()=0;

protected:
  //void defineProperty(const std::string& _propname, const std::string& _proptype, prophfn_t _handler);
  //inline void setObjDefDecls(std::set<std::string> _odd) {c_objdef_decls.merge(_odd);};
  void defineProperty(PropertyInterfaceSP _prop);
  void loadProperties(Reader& _reader);

public:
  virtual void deserialize(Reader& _reader)=0;
  virtual void deserializeProperties(Reader& _reader)=0;
  virtual std::string str() const=0;

private:
  struct pdkey {
    pdkey(const std::string& _name, const int32_t _index);
    bool operator<(const pdkey& other) const;
    bool operator==(const pdkey& other) const;
    std::string name;
    int32_t index;
  };
  std::map<pdkey, PropertyInterfaceSP> c_propdefs;
  //std::map<std::string, prophdef> c_propdefs;
  //std::set<std::string> c_objdef_decls;
  //std::map<std::string, objdef> c_objdefs;
};

typedef std::shared_ptr<Saveable> SaveableSP;

#endif
