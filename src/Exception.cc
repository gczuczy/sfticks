
#include "Exception.hh"

namespace SFT {

  Exception::Exception(const std::string _file, int _line, const std::string _func, const std::string _err):
    c_file(_file), c_line(_line), c_func(_func), c_error(_err){
  }

  Exception::Exception(const std::string _err): c_error(_err), c_line(0) {
  }

  Exception::~Exception() {
  }

  const char* Exception::what() const noexcept {
    if ( c_line ) {
      static char buff[128];
      snprintf(buff, 127, "%s:%i/%s - %s",
	       c_file.c_str(), c_line, c_func.c_str(),
	       c_error.c_str());
    }
    return c_error.c_str();
  }

}
