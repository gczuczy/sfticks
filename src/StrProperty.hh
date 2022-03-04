
#ifndef SFT_STRPROPERTY_H
#define SFT_STRPROPERTY_H

#include "SaveProperty.hh"

class StrProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };

public:
  StrProperty() = delete;
  StrProperty(const StrProperty&) = delete;
  StrProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~StrProperty();

  inline const std::string& value() const {return c_value;};


private:
  std::string c_value;
};

#endif

