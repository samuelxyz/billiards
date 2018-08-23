/*
 * Ball.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: Samuel Tan
 */

#include <Constants.h>
#include <entity/Ball.h>
#include <Table.h>
#include <Vec3.h>
#include <Vertex.h>
#include <cmath>
#include <forward_list>
#include <vector>

namespace billiards { namespace entity {

  Ball::Ball(gameplay::Table& table,
      const math::Vec2& position, const math::Vec2& velocity,
      float radius, float mass, const math::Vec4& color)
  : table(table), position(position), velocity(velocity),
    radius(radius), mass(mass), color(color)
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
    accelerate();
    move();
    collide();
    contain();
  }

  void Ball::accelerate()
  {
    velocity += table.getStats().gravity;

    // rolling friction
    if (!velocity.isZero())
    {
      // friction impulse is proportional to mass so
      // we'll just handle delta-v instead of bothering
      math::Vec2 frictionDV(-velocity);
      frictionDV.scaleTo(table.getStats().friction *
          ROLLING_FRICTION_RATIO);
      if (frictionDV > velocity)
        velocity = math::Vec2();
      else
        velocity += frictionDV;
    }
  }

  void Ball::move()
  {
    position += velocity;
  }

  void Ball::collide()
  {
    for (Ball* ball : table.getBallList())
      if (ball != this)
        collide(*ball);
  }

  void Ball::collide(Ball& other)
  {
    // simplify to 1d

    //    -r      r    min     max
    // <--(---0---)-----(---d---)--> axis along centers
    //      *this         other

    math::Vec2 rayToOther = other.position - position;
    float otherMin = rayToOther.getLength() - other.radius;

    if (otherMin >= radius)
      return; // no overlap

    float overlap = radius - otherMin; // guaranteed >0
    float totalMass = mass + other.mass;

    // project out of collision
    math::Vec2 dx(rayToOther);
    dx.scaleTo(overlap * mass/totalMass);
    position -= dx;
    dx.scaleTo(overlap * other.mass/totalMass);
    other.position += dx;

    // adjust velocities

    //    vel: 0           vel: dv
    //  ( *this  ) <------( other )   <--- axis along centers --->
    //              vPerp     |
    //     components:  vPara |
    //                        V

    math::Vec2 dv = other.velocity - velocity;
    rayToOther = other.position - position; // update this since we projected out
    float axisAngle = rayToOther.getAngle();
    dv.rotateBy(axisAngle);

    float vPerp = dv.x; // will probably be negative if colliding
    if (vPerp >= 0)
      return; // they don't apply any impulse to each other

    // in the space of our along-centers axis -- will rotate later for abs.
    // this receives dp, other receives -dp
    // dp could be the whole incoming relative momentum of other, if elastic
    math::Vec2 dp;

    // perpendicular impulse applied to each
    dp.x = vPerp * totalMass;

    if (table.getStats().friction && dv.y != 0)
    {
      float vPara = dv.y;
      float frictionDirection = vPara / std::fabs(vPara);

      // friction can't reverse the direction of vPara, only reduce it to 0
      float frictionImpulseMagnitude =
          std::min(std::fabs(vPara), std::fabs(vPerp)) *
          table.getStats().friction * totalMass;

      dp.y = frictionImpulseMagnitude * frictionDirection;
    }

    // prepare dp and preview result
    dp.rotateBy(axisAngle);
    dp *= (1 + table.getStats().bounciness) / 2;
    math::Vec2 finalThisVelocity = velocity + dp/mass;
    math::Vec2 finalOtherVelocity = other.velocity - dp/other.mass;
    math::Vec2 finalDV = finalOtherVelocity - finalThisVelocity;

    if (finalDV > dv)
    {
      // TODO: figure out how to limit finalDV to length of dv
      // current hack works decently:
      math::Vec2 clampedFinalDV(finalDV);
      clampedFinalDV.scaleTo(dv.getLength());
      dp.scaleTo((dv - clampedFinalDV).getLength() * (mass * other.mass / totalMass));
      dp *= (1 + table.getStats().bounciness) / 2;
    }

    // apply impulses
    velocity += dp / mass;
    other.velocity -= dp / other.mass;
  }

  void Ball::contain()
  {
    const gameplay::Table::Stats& stats = table.getStats();

    // left and right borders ---------------------------

    if (position.x - radius < 0)
    {
      position.x = 0 + radius;

      math::Vec2 dv(-velocity.x * (1+stats.bounciness));
      if (std::fabs(velocity.y) < std::fabs(dv.x * stats.friction))
        dv.y = -velocity.y;
      else if (velocity.y)
        dv.y = (-velocity.y / std::fabs(velocity.y)) *
        std::fabs(dv.x * stats.friction);
      velocity += dv;
    }
    else if (position.x + radius > stats.width)
    {
      position.x = table.getStats().width - radius;

      math::Vec2 dv(-velocity.x * (1+stats.bounciness));
      if (std::fabs(velocity.y) < std::fabs(dv.x * stats.friction))
        dv.y = -velocity.y;
      else if (velocity.y)
        dv.y = (-velocity.y / std::fabs(velocity.y)) *
        std::fabs(dv.x * stats.friction);
      velocity += dv;
    }

    // top and bottom borders -----------------------------------------

    if (position.y - radius < 0)
    {
      position.y = 0 + radius;

      math::Vec2 dv(0, -velocity.y * (1+stats.bounciness));
      if (std::fabs(velocity.x) < std::fabs(dv.y * stats.friction))
        dv.x = -velocity.x;
      else if (velocity.x)
        dv.x = (-velocity.x / std::fabs(velocity.x)) *
        std::fabs(dv.y * stats.friction);
      velocity += dv;
    }
    else if (position.y + radius > stats.height)
    {
      position.y = table.getStats().height - radius;

      math::Vec2 dv(0, -velocity.y * (1+stats.bounciness));
      if (std::fabs(velocity.x) < std::fabs(dv.y * stats.friction))
        dv.x = -velocity.x;
      else if (velocity.x)
        dv.x = (-velocity.x / std::fabs(velocity.x)) *
        std::fabs(dv.y * stats.friction);
      velocity += dv;
    }
  }

} /* namespace entity */
} /* namespace billiards */
