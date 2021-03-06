/*
 * Vec2.cpp
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#include <Vec2.h>
#include <cmath>

namespace billiards { namespace math {

  // --- CONSTRUCTORS ---

  Vec2::Vec2(float x, float y) // both parameters default to 0
  : x(x), y(y)
  {
  }

  // --- OPERATORS ---

  Vec2 operator+(const Vec2& v1, const Vec2& v2)
  {
    return Vec2(v1.x + v2.x, v1.y + v2.y);
  }

  Vec2 operator-(const Vec2& v1, const Vec2& v2)
  {
    return Vec2(v1.x - v2.x, v1.y - v2.y);
  }

  Vec2 operator*(const Vec2& v, float d)
  {
    return Vec2(v.x * d, v.y * d);
  }
  Vec2 operator*(float d, const Vec2& v)
  {
    return Vec2(v.x * d, v.y * d);
  }

  Vec2 operator/(const Vec2& v, float d)
  {
    return 1/d * v;
  }

  Vec2& Vec2::operator+=(const Vec2& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vec2& Vec2::operator-=(const Vec2& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vec2& Vec2::operator*=(float factor)
  {
    x *= factor;
    y *= factor;
    return *this;
  }

  Vec2 Vec2::operator-()
  {
    return Vec2() - *this;
  }

  // Dot product
  float operator*(const Vec2& v1, const Vec2& v2)
  {
    return v1.x * v2.x + v1.y * v2.y;
  }

  std::ostream& operator<<(std::ostream& out, const Vec2& v)
  {
    out << "Vec2(" << v.x << ", " << v.y << ")";
    return out;
  }

  bool operator==(const Vec2& lhs, const Vec2& rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }

  // length comparison
  bool operator<(const Vec2& lhs, const Vec2& rhs)
  {
    return lhs.getLength() < rhs.getLength();
  }
  bool operator>(const Vec2& lhs, const Vec2& rhs)
  {
    return rhs < lhs;
  }
  bool operator<=(const Vec2& lhs, const Vec2& rhs)
  {
    return !(lhs > rhs);
  }
  bool operator>=(const Vec2& lhs, const Vec2& rhs)
  {
    return !(lhs < rhs);
  }

  // --- MUTATORS ---

  Vec2& Vec2::setPolar(float length, float angle)
  {
    x = length;
    y = 0;
    rotateBy(angle);
    return *this;
  }

  Vec2& Vec2::rotateBy(float angle)
  {
    float oldX = x;
    float oldY = y;
    double cosa = std::cos(static_cast<double>(angle));
    double sina = std::sin(static_cast<double>(angle));

    x = static_cast<float>(cosa * oldX - sina * oldY);
    y = static_cast<float>(sina * oldX + cosa * oldY);

    return *this;
  }

  Vec2& Vec2::rotateTo(float targetAngle)
  {
    return rotateBy(targetAngle - getAngle());
  }

  Vec2& Vec2::scaleTo(float targetLength)
  {
    // special case
    if (isZero())
      x = targetLength;

    *this *= (targetLength / getLength());

    return *this;
  }

  float Vec2::getLength() const
  {
    return static_cast<float>(hypot(
        static_cast<double>(x),
        static_cast<double>(y)
    ));
  }

  float Vec2::getAngle() const
  {
    return static_cast<float>(atan2(
        static_cast<double>(y),
        static_cast<double>(x)
    ));
  }

  bool Vec2::isZero() const
  {
    return (x == 0) && (y == 0);
  }

} /* namespace math */
} /* namespace billiards */
