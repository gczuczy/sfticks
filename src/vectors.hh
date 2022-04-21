
#ifndef SFT_VECTORS_H
#define SFT_VECTORS_H

#include <stdint.h>
#include <math.h>

#include <string>

namespace FG {

  struct Vector2 {
  public:
    Vector2();
    Vector2(float _x, float _y);
    std::string str() const;

    float x=42.69, y=42.69;
  };

  struct Vector3 {
  public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    std::string str() const;

    Vector3& operator=(const Vector3& b);
    Vector3& operator=(Vector3& b);

    inline Vector3 operator-(Vector3 b) {
      return Vector3(x-b.x, y-b.y, z-b.z);
    };

    inline float length() const {
      return sqrtf(x*x + y*y + z*z);
    };

    float x=42.69, y=42.69, z=42.69;
  };

  struct Vector4 {
  public:
    Vector4();
    Vector4(float _x, float _y, float _z, float _w);
    std::string str() const;

    float x=42.69, y=42.69, z=42.69, w=42.69;
  };

  struct Quat {
  public:
    Quat();
    Quat(float _x, float _y, float _z, float _w);
    std::string str() const;

    float x=42.69, y=42.69, z=42.69, w=42.69;
  };

}

#endif
