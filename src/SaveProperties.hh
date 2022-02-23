
#ifndef SFT_SAVEPROPERTIES_H
#define SFT_SAVEPROPERTIES_H

#include "Reader.hh"

#include <stdint.h>

#include <string>
#include <vector>

enum class PropertyType: int8_t {
  IntProperty=0,
  ObjectProperty,
  ArrayProperty,
  InterfaceProperty,
  StrProperty,
  StructProperty,
  EnumProperty,
  FloatProperty
};

class SaveProperty {
public:
  SaveProperty(const SaveProperty&) = delete;
  SaveProperty(std::string& _name, std::string& _type, int32_t _index);
protected:
  SaveProperty(std::string& _name, int32_t _index);
public:
  virtual ~SaveProperty()=0;

  inline const std::string& name() const {return c_name;};
  inline PropertyType type() const {return c_type;};
  inline int32_t index() const {return c_index;};

  static std::shared_ptr<SaveProperty> factory(Reader& _reader);
protected:
  static std::shared_ptr<SaveProperty> factory(PropertyType _type, Reader& _reader, std::string _name,
					       int32_t _index, int32_t _size);

protected:
  std::string c_name;
  int32_t c_index;
  PropertyType c_type;
};

class IntProperty: public SaveProperty {
public:
  IntProperty() = delete;
  IntProperty(const IntProperty&) = delete;
  IntProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~IntProperty();

  inline int32_t value() const {return c_value;};

private:
  int32_t c_value;
};

class ObjectProperty: public SaveProperty {
public:
  ObjectProperty() = delete;
  ObjectProperty(const ObjectProperty&) = delete;
  ObjectProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~ObjectProperty();

  inline const std::string& levelName() const {return c_levelname;};
  inline const std::string& pathName() const {return c_pathname;};

private:
  std::string c_levelname, c_pathname;
};

class ArrayProperty: public SaveProperty {
public:
  ArrayProperty() = delete;
  ArrayProperty(const ArrayProperty&) = delete;
  ArrayProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~ArrayProperty();

  inline PropertyType valueType() const {return c_valuetype;};

private:
  PropertyType c_valuetype;
  std::vector<std::shared_ptr<SaveProperty> > c_data;
};

class InterfaceProperty: public SaveProperty {
public:
  InterfaceProperty() = delete;
  InterfaceProperty(const InterfaceProperty&) = delete;
  InterfaceProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size, bool _skip=true);
  virtual ~InterfaceProperty();

  inline const std::string& levelName() const {return c_levelname;};
  inline const std::string& pathName() const {return c_pathname;};

private:
  std::string c_levelname, c_pathname;
};

class StrProperty: public SaveProperty {
public:
  StrProperty() = delete;
  StrProperty(const StrProperty&) = delete;
  StrProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~StrProperty();

  inline const std::string& value() const {return c_value;};

private:
  std::string c_value;
};

class StructProperty: public SaveProperty {
public:
  StructProperty() = delete;
  StructProperty(const StructProperty&) = delete;
  StructProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~StructProperty();

private:
};

class EnumProperty: public SaveProperty {
public:
  EnumProperty() = delete;
  EnumProperty(const EnumProperty&) = delete;
  EnumProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~EnumProperty();

private:
  std::string c_enumtype, c_value;
};

class FloatProperty: public SaveProperty {
public:
  FloatProperty() = delete;
  FloatProperty(const FloatProperty&) = delete;
  FloatProperty(std::string& _name, Reader& _reader, int32_t _index, int32_t _size);
  virtual ~FloatProperty();

  inline float value() const {return c_value;};

private:
  float c_value;
};
#endif
