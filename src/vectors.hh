
#ifndef SFT_VECTORS_H
#define SFT_VECTORS_H

#include <stdint.h>

class Vector2 {
public:
  Vector2();
  Vector2(float _x, float _y);

  inline float x() const {return c_x;};
  inline float y() const {return c_y;};

private:
  float c_x,c_y;
};

class Vector3 {
public:
  Vector3();
  Vector3(float _x, float _y, float _z);

  inline float x() const {return c_x;};
  inline float y() const {return c_y;};
  inline float z() const {return c_z;};

private:
  float c_x, c_y, c_z;
};

class Vector4 {
public:
  Vector4();
  Vector4(float _x, float _y, float _z, float _w);

  inline float x() const {return c_x;};
  inline float y() const {return c_y;};
  inline float z() const {return c_z;};
  inline float w() const {return c_w;};

private:
  float c_x, c_y, c_z, c_w;
};

#endif
