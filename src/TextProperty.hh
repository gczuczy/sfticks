
#ifndef SFT_TEXTPROPERTY_H
#define SFT_TEXTPROPERTY_H

#include "SaveProperty.hh"

class TextProperty: public SaveProperty {
public:
  enum class HistoryType: int8_t {
    None=-1,
      Base = 0,
      NamedFormat,
      OrderedFormat,
      ArgumentFormat,
      AsNumber,
      AsPercent,
      AsCurrency,
      AsDate,
      AsTime,
      AsDateTime,
      TransForm,
      StringTableEntry,
      TextGenerator
  };

  class Header: public SaveProperty::Header {
  public:
    Header(Reader &_, std::string _name, int32_t _index);
    virtual ~Header();
  };
public:
  TextProperty() = delete;
  TextProperty(const TextProperty&) = delete;
  TextProperty(std::shared_ptr<Header> _header, Reader& _reader);
  virtual ~TextProperty();

private:
  int32_t c_flags;
  HistoryType c_historytype;
  // Base
  std::string c_namespace, c_key, c_value;
  // None
  bool c_has_culture_invariant_string;
  std::string c_culture_invariant_string;
};

#endif
