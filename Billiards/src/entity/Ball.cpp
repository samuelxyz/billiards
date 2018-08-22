/*
 * Ball.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: Samuel Tan
 */

#include <entity/Ball.h>
#include <Vertex.h>
#include <Constants.h>

namespace billiards { namespace entity {

  Ball::Ball(const math::Vec2& position, float radius,
      const math::Vec4& color)
  : position(position), radius(radius), color(color)
  {
  }

  Ball::~Ball()
  {
  }

  void Ball::render(graphics::FanBatchRenderer& renderer)
  {
    const unsigned int numTriangles = radius * 2;

    graphics::Fan fan;

    fan.push_back({math::Vec3(position), color});

    math::Vec2 v(radius);
    for (unsigned int i = 0; i < numTriangles; ++i)
    {
      fan.push_back({math::Vec3(position + v), color});
      v.rotateBy(Constants::TWO_PI / numTriangles);
    }
    fan.push_back({math::Vec3(position + v), color});

    renderer.submit(fan);
  }

  void Ball::update()
  {
  }

} /* namespace entity */
} /* namespace billiards */
