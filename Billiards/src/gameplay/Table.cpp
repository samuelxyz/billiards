/*
 * Table.cpp
 *
 *  Created on: Aug 22, 2018
 *      Author: Samuel Tan
 */

#include <Table.h>
#include <Constants.h>

namespace billiards { namespace gameplay {

  Table::Table()
  : stats { Constants::TABLE_PANE_WIDTH, Constants::TABLE_PANE_HEIGHT, math::Vec2(), 0.2f, 0.5f },
    ballList()
  {
  }

  Table::~Table()
  {
    clear();
  }

  void Table::update()
  {
    for (entity::Ball* ball : ballList)
      ball->update();
  }

  void Table::render(graphics::FanBatchRenderer& renderer) const
  {
    for (entity::Ball* ball : ballList)
      ball->render(renderer);
  }

  void Table::add(entity::Ball* ball)
  {
    ballList.push_front(ball);
  }

  void Table::destroy(entity::Ball* ball)
  {
    delete ball;
    ballList.remove(ball);
  }

  void Table::clear()
  {
    for (entity::Ball* ball : ballList)
      delete ball;
    ballList.clear();
  }

} /* namespace gameplay */
} /* namespace billiards */
