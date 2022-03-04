
#ifndef SFT_INTPROPERTY_H
#define SFT_INTPROPERTY_H

#include "SaveProperty.hh"

// IntProperty
class IntProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index=0);
    Header(std::string _name, int32_t _index=0);
    virtual ~Header();
  };
public:
  IntProperty() = delete;
  IntProperty(const IntProperty&) = delete;
  IntProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~IntProperty();

  inline int32_t value() const {return c_value;};


private:
  int32_t c_value;
};


#endif
