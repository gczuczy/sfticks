
#ifndef SFT_NAMEPROPERTY_H
#define SFT_NAMEPROPERTY_H

#include "SaveProperty.hh"

class NameProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };
public:
  NameProperty() = delete;
  NameProperty(const NameProperty&) = delete;
  NameProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~NameProperty();

  inline const std::string& value() const {return c_value;};

private:
  std::string c_value;
};

#endif
