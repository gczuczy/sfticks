
#ifndef SFT_BYTEPROPERTY_H
#define SFT_BYTEPROPERTY_H

#include "SaveProperty.hh"

class ByteProperty: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    Header(std::string _bytetype, std::string _name, int32_t _index);
    virtual ~Header();

    inline std::string bytetype() const {return c_bytetype;};

  private:
    std::string c_bytetype;
  };
public:
  ByteProperty() = delete;
  ByteProperty(const ByteProperty&) = delete;
  ByteProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~ByteProperty();

  inline const std::string& type() const {return c_bytetype;};
  inline const std::string& value() const {return c_value;};

private:
  std::string c_bytetype;
  std::string c_value;
};

#endif
