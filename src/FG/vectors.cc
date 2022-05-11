
#include <stdio.h>
#include "FG/vectors.hh"

namespace FG {

  Vector2::Vector2() {
  }

  Vector2::Vector2(float _x, float _y): x(_x), y(_y) {
  }

  std::string Vector2::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector2(%.3f, %.3f)", x, y);
    return std::string(buffer, len);
  }

  Vector3::Vector3() {
  }

  Vector3::Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {
  }

  std::string Vector3::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector3(%.3f, %.3f, %.3f)", x, y, z);
    return std::string(buffer, len);
  }

  Vector3& Vector3::operator=(const Vector3& b) {
    x = b.x;
    y = b.y;
    z = b.z;
    return *this;
  }

  Vector3& Vector3::operator=(Vector3& b) {
    x = b.x;
    y = b.y;
    z = b.z;
    return *this;
  }

  Vector4::Vector4() {
  }

  Vector4::Vector4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {
  }

  std::string Vector4::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector4(%.3f, %.3f, %.3f, %.3f)", x, y, z, w);
    return std::string(buffer, len);
  }

  Quat::Quat() {
  }

  Quat::Quat(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {
  }

  std::string Quat::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Quat(%.3f, %.3f, %.3f, %.3f)", x, y, z, w);
    return std::string(buffer, len);
  }

}
