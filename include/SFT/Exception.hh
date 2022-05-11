
#ifndef SFT_EXCEPTION_H
#define SFT_EXCEPTION_H

#include <exception>
#include <string>

#define EXCEPTION(errstr) throw SFT::Exception(__FILE__, __LINE__, __PRETTY_FUNCTION__, errstr)

namespace SFT {

  class Exception: public std::exception {
  public:
    Exception() = delete;
    Exception(const std::string _file, int _line, const std::string _func, const std::string _err);
    Exception(const std::string _err);
    virtual ~Exception();
    virtual const char* what() const noexcept;

  private:
    std::string c_error;
    std::string c_file, c_func;
    int c_line;
  };

}

#endif
