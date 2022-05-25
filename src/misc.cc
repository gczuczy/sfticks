
#include "misc.hh"

#include <stdarg.h>

#include <charconv>
#include <string_view>
#include <system_error>

std::string strprintf(const char* fmt...) {
  char buffer[2048];

  va_list ap;
  va_start(ap,fmt);
  int len = vsnprintf(buffer, 2047, fmt, ap);
  va_end(ap);
  return std::string(buffer, len);
}

bool strtoint32(const std::string& _str, int32_t& _retval) {
  auto [ptr, ec] {std::from_chars(_str.data(), _str.data()+_str.size(), _retval)};

  if ( ec == std::errc::invalid_argument ) {
#ifdef SFT_DEBUG_MISC
    printf("Cannot convert '%s' to int\n", _str.c_str());
#endif
    return false;
    //EXCEPTION("Cannot convert to int");
  } else if ( ec == std::errc::result_out_of_range ) {
#ifdef SFT_DEBUG_MISC
    printf("Cannot convert '%s' to int, out of range\n", _str.c_str());
#endif
    return false;
    //	EXCEPTION("Cannot convert to int, out of range");
  }
  return true;
}

template<>
uint32_t fromstr<uint32_t>(const std::string& _str) {
  char *end;
  return std::strtoul(_str.c_str(), &end, 10);
};

std::string tolower(const std::string& _str, size_t _len) {
  std::string instr;
  if ( _len == 0 ) {
    instr = _str;
  } else {
    instr = _str.substr(0, _len);
  }

  std::transform(instr.begin(), instr.end(), instr.begin(),
		 [](unsigned char c) {return std::tolower(c);});

  return instr;
}
