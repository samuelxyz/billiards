/*
 * Ball.h
 *
 *  Created on: Aug 21, 2018
 *      Author: Samuel Tan
 */

#ifndef BALL_H_
#define BALL_H_

#include <Table.h>
#include <Vec4.h>

namespace billiards { namespace entity {

  class Ball
  {
      friend class gameplay::Table;

    protected:
      gameplay::Table& table;
      math::Vec2 position, velocity;
      float radius, mass;
      math::Vec4 color;
      bool beingDragged;
      static constexpr float ROLLING_FRICTION_RATIO = 0.01;

    public:
      Ball(gameplay::Table& table,
          const math::Vec2& position, const math::Vec2& velocity,
          float radius, float mass, const math::Vec4& color);
      virtual ~Ball();

      virtual void render(graphics::FanBatchRenderer& renderer);
      virtual void update();

      bool containsPoint(const math::Vec2& point);

    protected:
      void accelerate();
      void move();
      void collide();
      void collide(Ball& other);
      void contain();
  };

} /* namespace entity */
} /* namespace billiards */

#endif /* BALL_H_ */
