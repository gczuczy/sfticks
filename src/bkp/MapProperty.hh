
#ifndef SFT_MAPPROPERTY_H
#define SFT_MAPPROPERTY_H

#include "SaveProperty.hh"

#include <list>

class MapProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();

    inline PropertyType keytype() const {return c_key_type;};
    inline PropertyType valuetype() const {return c_value_type;};

  private:
    PropertyType c_key_type, c_value_type;
  };

public:
  MapProperty() = delete;
  MapProperty(const MapProperty&) = delete;
  MapProperty(std::shared_ptr<Header> _name, Reader& _reader);
  virtual ~MapProperty();

  inline PropertyType keytype() const {return c_key_type;};
  inline PropertyType valuetype() const {return c_value_type;};

private:
  typedef std::pair<std::shared_ptr<SaveProperty>,std::shared_ptr<SaveProperty> > datapair;
  PropertyType c_key_type, c_value_type;
  // for now we store them in pairs
  // real map would require a custom compare operator with sub-type checking
  std::list<datapair> c_data;
};

#endif
