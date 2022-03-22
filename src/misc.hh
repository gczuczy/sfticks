
#ifndef FGT_MISC_HH
#define FGT_MISC_HH

#include <string>

__attribute__((format(printf, 1, 2))) std::string strprintf(const char* fmt...);
bool strtoint32(const std::string& _str, int32_t& _retval);

#endif
