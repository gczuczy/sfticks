
#include <exception>
#include <string>

class Exception: public std::exception {
public:
  Exception() = delete;
  Exception(const std::string _err);
  virtual ~Exception();
  virtual const char* what() const noexcept;

private:
  std::string c_error;
  
};
