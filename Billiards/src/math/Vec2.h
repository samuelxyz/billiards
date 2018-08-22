/*
 * Vec2.h
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#ifndef VEC2_H_
#define VEC2_H_

#include <iostream>

namespace billiards { namespace math {

  struct Vec2
  {
      float x, y;

      Vec2(float x = 0, float y = 0);
      // copy constructor is default

      friend Vec2 operator+(const Vec2& v1, const Vec2& v2);
      friend Vec2 operator-(const Vec2& v1, const Vec2& v2);
      friend Vec2 operator*(const Vec2& v, float d);
      friend Vec2 operator*(float d, const Vec2& v);
      friend Vec2 operator/(const Vec2& v, float d);

      Vec2& operator+=(const Vec2& rhs);
      Vec2& operator-=(const Vec2& rhs);
      Vec2& operator*=(float factor);
      Vec2 operator-();
      // operator= has a good default

      // dot product
      friend float operator*(const Vec2& v1, const Vec2& v2);

      friend std::ostream& operator<<(std::ostream& out, const Vec2& v);

      friend bool operator==(const Vec2&, const Vec2&);

      // comparing magnitudes
      friend bool operator<(const Vec2&, const Vec2&);
      friend bool operator>(const Vec2&, const Vec2&);
      friend bool operator<=(const Vec2&, const Vec2&);
      friend bool operator>=(const Vec2&, const Vec2&);

      // mutators
      Vec2& setPolar(float length, float angle);
      Vec2& rotateBy(float angle);
      Vec2& rotateTo(float targetAngle);
      Vec2& scaleTo(float targetLength);

      // accessors
      float getLength() const;
      float getAngle() const; // returns 0 if isZero
      bool isZero() const;
  };

} /* namespace math */
} /* namespace billiards */

#endif /* VEC2_H_ */
