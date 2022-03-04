
#ifndef SFT_INTERFACEPROPERTY_H
#define SFT_INTERFACEPROPERTY_H

#include "SaveProperty.hh"

class InterfaceProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    Header(std::string _name, int32_t _index);
    virtual ~Header();
  };

public:
  InterfaceProperty() = delete;
  InterfaceProperty(const InterfaceProperty&) = delete;
  InterfaceProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~InterfaceProperty();

  inline const std::string& levelName() const {return c_levelname;};
  inline const std::string& pathName() const {return c_pathname;};

private:
  std::string c_levelname, c_pathname;
};

#endif
