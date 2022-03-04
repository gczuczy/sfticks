
#ifndef SFT_BOOLPROPERTY_H
#define SFT_BOOLPROPERTY_H

#include "SaveProperty.hh"

class BoolProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };
public:
  BoolProperty() = delete;
  BoolProperty(const BoolProperty&) = delete;
  BoolProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~BoolProperty();

  inline bool value() const {return c_value;};

private:
  bool c_value;
};

#endif

