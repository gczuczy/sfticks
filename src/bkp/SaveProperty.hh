
#ifndef SFT_SAVEPROPERTY_H
#define SFT_SAVEPROPERTY_H

#include <stdint.h>

#include <string>
#include <memory>

#include "Reader.hh"

enum class PropertyType: int8_t {
  IntProperty=0,
  ObjectProperty,
  ArrayProperty,
  InterfaceProperty,
  StrProperty,
  StructProperty,
  EnumProperty,
  FloatProperty,
  BoolProperty,
  TextProperty,
  NameProperty,
  ByteProperty,
  Int64Property,
  MapProperty,
};

std::string ptypestr(PropertyType _pt);
PropertyType ptype(const std::string &_v);

class SaveProperty {
protected:
  class Header {
  protected:
    Header() = delete;
    Header(std::string& _name, int32_t _index);
    Header(const Header&) = delete;
    Header(PropertyType _pt, Reader& _r, std::string& _name, int32_t _index);
    Header(PropertyType _pt, std::string& _name, int32_t _index);
  public:
    virtual ~Header()=0;

    inline PropertyType ptype() const {return c_ptype;};
    inline std::string name() const {return c_name;};
    inline int32_t index() const {return c_index;};

    static std::shared_ptr<Header> factory(Reader &_r, PropertyType _pt, std::string _name, int32_t _index);

  protected:
    PropertyType c_ptype;
    std::string c_name;
    int32_t c_index;
    int32_t c_len;
  }; // Header
public:
  SaveProperty(const SaveProperty&) = delete;
  SaveProperty(std::string& _name, std::string& _type, int32_t _index);
protected:
  SaveProperty(PropertyType _type, std::string& _name, int32_t _index);
  SaveProperty(PropertyType _type, int32_t _index);
  SaveProperty(std::shared_ptr<Header> _header);


public:
  virtual ~SaveProperty()=0;

  inline const std::string& name() const {return c_name;};
  inline PropertyType type() const {return c_type;};
  inline int32_t index() const {return c_index;};

  static std::shared_ptr<SaveProperty> factory(Reader& _reader);
protected:
  static std::shared_ptr<SaveProperty> factory(std::shared_ptr<Header> _header, Reader& _reader);

protected:
  std::string c_name;
  int32_t c_index;
  PropertyType c_type;
};

#endif
