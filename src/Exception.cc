
#include "Exception.hh"

Exception::Exception(const std::string _err): c_error(_err) {
}

Exception::~Exception() {
}

const char* Exception::what() const noexcept {
  return c_error.c_str();
}

