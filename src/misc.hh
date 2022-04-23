
#ifndef FGT_MISC_HH
#define FGT_MISC_HH

#include <string>
#include <cstdlib>
#include <stdint.h>

__attribute__((format(printf, 1, 2))) std::string strprintf(const char* fmt...);
bool strtoint32(const std::string& _str, int32_t& _retval);

template<typename T>
T fromstr(const std::string& _str) {
  return T(); // needs specialization
};

// uint32_t specialization
template<>
uint32_t fromstr<uint32_t>(const std::string& _str);

#endif
