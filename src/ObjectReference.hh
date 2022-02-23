
#ifndef SFT_OBJECTREFERENCE_H
#define  SFT_OBJECTREFERENCE_H

#include <string>

#include "Reader.hh"

class ObjectReference {
public:
  ObjectReference() = delete;
  ObjectReference(const ObjectReference&) = delete;
  ObjectReference(Reader& _r);
  ~ObjectReference();

  inline std::string levelName() const {return c_levelname;};
  inline std::string pathName() const {return c_pathname;};

private:
  std::string c_levelname;
  std::string c_pathname;
  
};


#endif
