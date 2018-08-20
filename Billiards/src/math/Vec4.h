/*
 * Vec4.h
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#ifndef VEC4_H_
#define VEC4_H_

namespace billiards { namespace math {

  struct Vec4
  {
    public:
      float x, y, z, w;

      Vec4(float x = 0, float y = 0, float z = 0, float w = 0);
  };

} /* namespace math */
} /* namespace billiards */

#endif /* VEC4_H_ */
