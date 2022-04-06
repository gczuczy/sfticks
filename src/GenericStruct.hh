
#ifndef SFT_GENERICSTRUCT_H
#define SFT_GENERICSTRUCT_H

#include "StructProperty.hh"

/*
  This class is holding the raw struct data from the dump, and later
  will be able to dump it as "serialization". No parsing is done.
  This is intended for those structs which are not needed for the project.
 */
class GenericStruct: public StructProperty<std::string> {
public:
  GenericStruct() = delete;
  GenericStruct(const std::string& _strtype, const std::string& _name, int32_t _index=0);
  virtual ~GenericStruct()=default;

  virtual void deserialize(Reader& _reader, int32_t _size);
  virtual void deserializeData(Reader& _reader);

private:
  std::string c_data;
};
typedef std::shared_ptr<GenericStruct> GenericStructSP;

#endif
