/*
 * Mat4.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef MAT4_H_
#define MAT4_H_

namespace billiards { namespace math {

  struct Mat4
  {
      float elements[16];

      Mat4(float diagonal = 0.0f);
      virtual ~Mat4();

      static Mat4 ortho(float left, float right, float bottom, float top);
  };

} /* namespace math */
} /* namespace billiards */

#endif /* MAT4_H_ */
