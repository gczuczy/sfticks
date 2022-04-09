
#include <stdio.h>
#include "vectors.hh"

namespace FG {

  Vector2::Vector2(): c_x(0), c_y(0) {
  }

  Vector2::Vector2(float _x, float _y): c_x(_x), c_y(_y) {
  }

  std::string Vector2::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector2(%.3f, %.3f)", c_x, c_y);
    return std::string(buffer, len);
  }

  Vector3::Vector3(): c_x(0), c_y(0), c_z(0) {
  }

  Vector3::Vector3(float _x, float _y, float _z): c_x(_x), c_y(_y), c_z(_z) {
  }

  std::string Vector3::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector3(%.3f, %.3f, %.3f)", c_x, c_y, c_z);
    return std::string(buffer, len);
  }

  Vector4::Vector4(): c_x(0), c_y(0), c_z(0), c_w(0) {
  }

  Vector4::Vector4(float _x, float _y, float _z, float _w): c_x(_x), c_y(_y), c_z(_z), c_w(_w) {
  }

  std::string Vector4::str() const {
    char buffer[128];
    int len;
    len = snprintf(buffer, 128, "Vector4(%.3f, %.3f, %.3f, %.3f)", c_x, c_y, c_z, c_w);
    return std::string(buffer, len);
  }

}
