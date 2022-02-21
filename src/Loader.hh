#include <string>
#include <stdint.h>

class Loader {
public:
  Loader(const std::string &_file);
  ~Loader();

private:
  std::string c_filename;
  int c_fd;
  uint64_t c_savesize;
  char *c_save;
  
};
