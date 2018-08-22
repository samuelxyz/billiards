/*
 * Table.h
 *
 *  Created on: Aug 22, 2018
 *      Author: Samuel Tan
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <entity/Ball.h>
#include <Vec2.h>
#include <forward_list>

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
      Stats stats;

      // dynamic allocation
      std::forward_list<entity::Ball*> ballList;

    public:
      Table();
      virtual ~Table();

      const Stats& getStats() const { return stats; }
      std::forward_list<entity::Ball*>& getBallList() { return ballList; }

      void update();
      void render(graphics::FanBatchRenderer& renderer) const;

      void add(entity::Ball* ball);
      void destroy(entity::Ball* ball);
      void clear();

  };

} /* namespace gameplay */
} /* namespace billiards */

#endif /* TABLE_H_ */
