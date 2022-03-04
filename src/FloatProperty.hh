
#ifndef SFT_FLOATPROPERTY_H
#define  SFT_FLOATPROPERTY_H

#include "SaveProperty.hh"

class FloatProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };
public:
  FloatProperty() = delete;
  FloatProperty(const FloatProperty&) = delete;
  FloatProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~FloatProperty();

  inline float value() const {return c_value;};

private:
  float c_value;
};

#endif
