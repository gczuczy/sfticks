
#ifndef SFT_OBJECTREFERENCE_H
#define SFT_OBJECTREFERENCE_H

#include <string>

class ObjectReference {
public:
  ObjectReference();
  ~ObjectReference();

  inline std::string& levelName() {return c_levelname;};
  inline std::string& pathName() {return c_pathname;};

private:
  std::string c_levelname;
  std::string c_pathname;
};

#endif
