/*
 * Mat4.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <Mat4.h>

namespace billiards { namespace math {

  Mat4::Mat4(float diagonal)
  {
    for (unsigned int i = 0; i < 4 * 4; ++i)
    {
      elements[i] = 0.0f;
    }

    if (diagonal == 0.0f)
      return;

    for (unsigned int i = 0; i < 4; ++i)
    {
      //       r   c
      elements[i + i * 4] = diagonal;
    }
  }

  Mat4::~Mat4()
  {
    // TODO Auto-generated destructor stub
  }

  Mat4 Mat4::ortho(float left, float right, float bottom, float top)
  {
    Mat4 result(1.0f);
    //              r   c
    result.elements[0 + 0 * 4] = 2.0f / (right - left);
    result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
    result.elements[0 + 3 * 4] = -(right + left) / (right - left);
    result.elements[1 + 3 * 4] = -(top + bottom) / (top - bottom);
    return result;
  }

} /* namespace math */
} /* namespace billiards */
