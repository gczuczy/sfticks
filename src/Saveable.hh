
#ifndef SFT_SAVEABLE_H
#define SFT_SAVEABLE_H

#include "Reader.hh"

#include <string>
#include <memory>
#include <functional>

class Saveable {
public:
  Saveable();
  virtual ~Saveable()=0;

protected:
  typedef std::function<void(Reader&, int32_t)> prophfn_t;
  void defineProperty(const std::string& _propname, const std::string& _proptype, prophfn_t _handler);
  void loadProperties(Reader& _reader);

public:
  virtual void deserialize(Reader& _reader)=0;
  virtual void deserializeProperties(Reader& _reader)=0;
  virtual std::string str() const=0;

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
  std::map<std::string, prophdef> c_propdefs;
};

typedef std::shared_ptr<Saveable> SaveableSP;

#endif
