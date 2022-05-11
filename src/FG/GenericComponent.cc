
#include "FG/GenericComponent.hh"
#include "SFT/Exception.hh"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace FG {

  GenericComponent::GenericComponent(Reader& _reader, ObjectHeader& _fgoh)
    : Component(ComponentType::Generic, _reader, _fgoh) {
    //printf("%s\n%s\n", parentEntityName().c_str(), instanceName().c_str());
    //EXCEPTION("GeneriComponent");
  }

  GenericComponent::~GenericComponent() {
  }

  void GenericComponent::deserialize(Reader &_reader) {
  }

  void GenericComponent::deserializeProperties(Reader &_reader) {
    _reader.store(c_properties);
  }

  void GenericComponent::dump(const std::string _file) {
    int fd;

    printf("GenericComponent::dump(%s), %li bytes\n", _file.c_str(), c_properties.size());
    if ( (fd = open(_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 ) {
      EXCEPTION("open() failed");
    }

    write(fd, c_properties.c_str(), c_properties.size());

    close(fd);
  }

  std::string GenericComponent::compdetails() {
    return "";
  }
}
