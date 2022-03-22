
#ifndef SFT_TRACE_H
#define SFT_TRACE_H

#include <stdint.h>

#include <string>
#include <map>
#include <memory>
#include <list>

#include "SavePropertyType.hh"

#define TRACE Trace t(__FILE__, __LINE__, __PRETTY_FUNCTION__)

class Trace {
  struct data {
    std::string descr;
    int level;
    std::map<std::string, std::string> details;
  };
  typedef std::shared_ptr<data> dataptr;
public:
  Trace(std::string _file, int _line, std::string _func);
  ~Trace();

  __attribute__((format(printf, 2, 3))) void printf(const char* fmt...);
  Trace& detail(const std::string &_name, const std::string& _value);
  Trace& detail(const std::string &_name, SavePropertyType _v);
  Trace& detail(const std::string &_name, int32_t _v);
  Trace& detail(const std::string &_name, uint32_t _v);
  Trace& detail(const std::string &_name, int64_t _v);
  Trace& detail(const std::string &_name, uint64_t _v);

  static void debug();
  std::string fulldescr(dataptr _data=0);
private:
  static int c_level;
  static std::list<dataptr> c_stack;
  std::string c_file, c_func;
  int c_line;
  dataptr c_data;
};


#endif
