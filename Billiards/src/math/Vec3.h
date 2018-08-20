/*
 * Vec3.h
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#ifndef VEC3_H_
#define VEC3_H_

#include <Vec2.h>

namespace billiards { namespace math {

  struct Vec3
  {
    public:
      float x, y, z;

      Vec3(float x = 0, float y = 0, float z = 0);
      Vec3(const Vec2& vec2, float z = 0);
  };

} /* namespace math */
} /* namespace billiards */

#endif /* VEC3_H_ */
