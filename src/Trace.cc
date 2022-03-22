
#include "Trace.hh"

#include <stdio.h>
#include <stdarg.h>

#define SFT_TRACE

int Trace::c_level=0;
std::list<Trace::dataptr> Trace::c_stack;

Trace::Trace(std::string _file, int _line, std::string _func): c_file(_file), c_line(_line), c_func(_func) {
  ++c_level;
  char buff[1024];
  int s = snprintf(buff, 1023, "%s:%i / %s",
		   c_file.c_str(), c_line, c_func.c_str());
#ifdef SFT_TRACE
  printf("Entering %s\n", buff);
#endif
  c_data = std::make_shared<data>();
  c_data->descr = std::string(buff, s);
  c_data->level = c_level;
  c_stack.push_back(c_data);
}

Trace::~Trace() {
#ifdef SFT_TRACE
  printf("Leaving %s\n", fulldescr().c_str());
#endif
  --c_level;
  c_stack.pop_back();
}

void Trace::printf(const char* fmt...) {
  for (int i=0; i<c_level; ++i) putchar(' ');

  va_list ap;
  va_start(ap,fmt);
  vprintf(fmt, ap);
  va_end(ap);
}

Trace& Trace::detail(const std::string &_name, const std::string& _value) {
  c_data->details[_name] = _value;
  return *this;
}

Trace& Trace::detail(const std::string &_name, SavePropertyType _v) {
  c_data->details[_name] = ptypestr(_v);
  return *this;
}

Trace& Trace::detail(const std::string &_name, int32_t _v) {
  c_data->details[_name] = std::to_string(_v);
  return *this;
}

Trace& Trace::detail(const std::string &_name, uint32_t _v) {
  c_data->details[_name] = std::to_string(_v);
  return *this;
}

Trace& Trace::detail(const std::string &_name, int64_t _v) {
  c_data->details[_name] = std::to_string(_v);
  return *this;
}

Trace& Trace::detail(const std::string &_name, uint64_t _v) {
  c_data->details[_name] = std::to_string(_v);
  return *this;
}

void Trace::debug() {
  ::printf("\nDebug stack:\n");
  for (auto it=c_stack.begin(); it != c_stack.end(); ++it) {
    auto data = *it;
    ::printf("%i: %s\n", data->level, data->descr.c_str());
    for (auto it2=data->details.begin(); it2!=data->details.end(); ++it2) {
      ::printf(" - %s: %s\n", it2->first.c_str(), it2->second.c_str());
    }
  }
}

std::string Trace::fulldescr(dataptr _data) {
  dataptr data(_data);
  if ( !data ) data = c_data;
  std::string str(data->descr);

  char buff[1024];
  int len;

  for (auto it = data->details.begin(); it != data->details.end(); ++it) {
    len = snprintf(buff, 1023, " %s:'%s'", it->first.c_str(), it->second.c_str());
    str += std::string(buff, len);
  }

  return str;
}

