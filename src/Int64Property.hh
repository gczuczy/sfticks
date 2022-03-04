
#ifndef SFT_INT64PROPERTY_H
#define SFT_INT64PROPERTY_H

#include "SaveProperty.hh"

class Int64Property: public SaveProperty {
public:
  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };

public:
  Int64Property() = delete;
  Int64Property(const Int64Property&) = delete;
  Int64Property(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~Int64Property();

  inline int64_t value() const {return c_value;};

private:
  int64_t c_value;
};

#endif
