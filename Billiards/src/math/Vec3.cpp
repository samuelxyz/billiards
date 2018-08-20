/*
 * Vec3.cpp
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#include <Vec3.h>

namespace billiards { namespace math {

  Vec3::Vec3(float x, float y, float z)
  : x(x), y(y), z(z)
  {
  }

  Vec3::Vec3(const Vec2& vec2, float z)
  : x(vec2.x), y(vec2.y), z(z)
  {
  }

} /* namespace math */
} /* namespace billiards */
