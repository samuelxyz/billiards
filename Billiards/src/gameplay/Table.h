/*
 * Table.h
 *
 *  Created on: Aug 22, 2018
 *      Author: Samuel Tan
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <FanBatchRenderer.h>
#include <Vec2.h>
#include <forward_list>

namespace billiards
{
  namespace graphics
  {
    class Window;
  } /* namespace graphics */

  namespace entity
  {
    class Ball;
  }
} /* namespace billiards */

namespace billiards { namespace gameplay {

  class Table
  {
    public:
      struct Stats
      {
        float width, height;
        math::Vec2 gravity;
        float friction, bounciness;
      };

    private:
      const graphics::Window& window;
      Stats stats;

      // dynamic allocation
      std::forward_list<entity::Ball*> ballList;

      struct
      {
          entity::Ball* target;
          math::Vec2 previousMousePos, idealBallOffset;
      } leftDrag;

      struct
      {
          bool active;
          math::Vec2 originalPos;
      } rightDrag;

    public:
      Table(const graphics::Window& window);
      virtual ~Table();

      const Stats& getStats() const { return stats; }
      std::forward_list<entity::Ball*>& getBallList() { return ballList; }

      void update();
      void render(graphics::FanBatchRenderer& renderer) const;

      void add(entity::Ball* ball);
      void destroy(entity::Ball* ball);
      void clear();

      void handleMouseButton(int button, int action);

    private:
      void checkDrag();
      void drag(entity::Ball* ball);
      void drag(math::Vec2& target, float sensitivity = 0.0000001);
  };

} /* namespace gameplay */
} /* namespace billiards */

#endif /* TABLE_H_ */
