
#include "misc.hh"

#include <stdarg.h>

#include <charconv>
#include <string_view>
#include <system_error>

std::string strprintf(const char* fmt...) {
  char buffer[128];

  va_list ap;
  va_start(ap,fmt);
  int len = vsnprintf(buffer, 127, fmt, ap);
  va_end(ap);
  return std::string(buffer, len);
}

bool strtoint32(const std::string& _str, int32_t& _retval) {
  auto [ptr, ec] {std::from_chars(_str.data(), _str.data()+_str.size(), _retval)};

  if ( ec == std::errc::invalid_argument ) {
#ifdef SFT_DEBUG
    printf("Cannot convert '%s' to int\n", _str.c_str());
#endif
    return false;
    //EXCEPTION("Cannot convert to int");
  } else if ( ec == std::errc::result_out_of_range ) {
#ifdef SFT_DEBUG
    printf("Cannot convert '%s' to int, out of range\n", _str.c_str());
#endif
    return false;
    //	EXCEPTION("Cannot convert to int, out of range");
  }
  return true;
}
