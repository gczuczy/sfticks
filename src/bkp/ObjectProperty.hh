
#ifndef SFT_OBJECTPROPERTY_H
#define SFT_OBJECTPROPERTY_H

#include "SaveProperty.hh"

class ObjectProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    Header(std::string _name, int32_t _index);
    virtual ~Header();
  };

public:
  ObjectProperty() = delete;
  ObjectProperty(const ObjectProperty&) = delete;
  ObjectProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~ObjectProperty();

  inline const std::string& levelName() const {return c_levelname;};
  inline const std::string& pathName() const {return c_pathname;};

private:
  std::string c_levelname, c_pathname;
};

#endif
