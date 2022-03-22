
#ifndef SFT_STRUCTPROPERTY_H
#define SFT_STRUCTPROPERTY_H

#include "SaveProperty.hh"

#include <map>

#include "vectors.hh"

class StructProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index, bool _nested=false);
    Header(std::string _strtype, std::string _name, int32_t _index);
    virtual ~Header();

    inline std::string structtype() const {return c_struct_type;};

  private:
    std::string c_struct_type;
  };

public:
  StructProperty() = delete;
  StructProperty(const StructProperty&) = delete;
  StructProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~StructProperty();

  inline const std::string& structType() const {return c_struct_type;};
  inline std::shared_ptr<SaveProperty> operator[](std::string& idx) {return c_members[idx];};

private:
  void parse(Reader& _reader);

private:
  std::string c_struct_type;
  std::map<std::string, std::shared_ptr<SaveProperty> > c_members;
  Vector3 c_box_min, c_box_max;
  Vector4 c_quat;
  Vector3 c_vector;
};

#endif
