/*
 * Ball.h
 *
 *  Created on: Aug 21, 2018
 *      Author: Samuel Tan
 */

#ifndef BALL_H_
#define BALL_H_

#include <FanBatchRenderer.h>
#include <Vec2.h>
#include <Vec4.h>

namespace billiards { namespace entity {

  class Ball
  {
    protected:
      math::Vec2 position;
      float radius;
      math::Vec4 color;

    public:
      Ball(const math::Vec2& position, float radius, const math::Vec4& color);
      virtual ~Ball();

      virtual void render(graphics::FanBatchRenderer& renderer);
      virtual void update();

    protected:
      void move();
      void collide();
      void collide(Ball& other);
      void contain();
  };

} /* namespace entity */
} /* namespace billiards */

#endif /* BALL_H_ */
