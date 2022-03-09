
#ifndef SFT_ARRAYPROPERTY_H
#define SFT_ARRAYPROPERTY_H

#include "SaveProperty.hh"

#include <vector>

class ArrayProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();

    inline PropertyType valuetype() const { return c_valuetype;};
    inline int32_t count() const {return c_count;};

  private:
    PropertyType c_valuetype;
    int32_t c_count;
  };
public:
  ArrayProperty() = delete;
  ArrayProperty(const ArrayProperty&) = delete;
  ArrayProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~ArrayProperty();

  inline PropertyType valueType() const {return c_valuetype;};

private:
  void parse(Reader &_reader);


private:
  PropertyType c_valuetype;
  std::vector<std::shared_ptr<SaveProperty> > c_data;
  int32_t c_count;
};

#endif
