
#include "FGGenericComponent.hh"
#include "Exception.hh"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

FGGenericComponent::FGGenericComponent(Reader& _reader, FGObjectHeader& _fgoh)
  : FGComponent(FGComponentType::Generic, _reader, _fgoh) {
  //printf("%s\n%s\n", parentEntityName().c_str(), instanceName().c_str());
  //EXCEPTION("GeneriComponent");
}

FGGenericComponent::~FGGenericComponent() {
}

void FGGenericComponent::deserialize(Reader &_reader) {
}

void FGGenericComponent::deserializeProperties(Reader &_reader) {
  _reader.store(c_properties);
}

void FGGenericComponent::dump(const std::string _file) {
  int fd;

  printf("FGGenericComponent::dump(%s), %li bytes\n", _file.c_str(), c_properties.size());
  if ( (fd = open(_file.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1 ) {
    throw Exception("open() failed");
  }

  write(fd, c_properties.c_str(), c_properties.size());

  close(fd);
}
