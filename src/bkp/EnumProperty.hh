
#ifndef SFT_ENUMPROPERTY_H
#define SFT_ENUMPROPERTY_H

#include "SaveProperty.hh"

class EnumProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    Header(std::string _name, int32_t _index, std::string _enumtype);
    virtual ~Header();

    inline std::string enumtype() const {return c_enumtype;};

  private:
    std::string c_enumtype;
  };
public:
  EnumProperty() = delete;
  EnumProperty(const EnumProperty&) = delete;
  EnumProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~EnumProperty();

private:
  std::string c_enumtype, c_value;
};

#endif
