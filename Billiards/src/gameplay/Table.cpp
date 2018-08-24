/*
 * Table.cpp
 *
 *  Created on: Aug 22, 2018
 *      Author: Samuel Tan
 */

#include <Table.h>

#include <Constants.h>
#include <Window.h>
#include <Ball.h>

namespace billiards { namespace gameplay {

  Table::Table(const graphics::Window& window)
  : window(window),
    stats { Constants::TABLE_PANE_WIDTH, Constants::TABLE_PANE_HEIGHT, math::Vec2(), 0.2f, 0.5f },
    ballList(),
    dragging(nullptr),
    previousMousePos()
  {
  }

  Table::~Table()
  {
    clear();
  }

  void Table::update()
  {
    checkDrag();

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

  void Table::handleMouseButton(int button, int action)
  {
    if (action == GLFW_PRESS && dragging == nullptr)
    {
      math::Vec2 clickPos = window.getMousePos();
      for (entity::Ball* b : ballList)
      {
        if (b->containsPoint(clickPos))
        {
          previousMousePos = clickPos;
          dragging = b;
          b->beingDragged = true;
          break;
        }
      }
    }

    else if (action == GLFW_RELEASE && dragging != nullptr)
    {
      dragging->beingDragged = false;
      dragging = nullptr;
    }
  }

  void Table::checkDrag()
  {
    if (dragging)
    {
      drag(dragging);
      previousMousePos = window.getMousePos();
    }
  }

  void Table::drag(entity::Ball* ball)
  {
    math::Vec2 dx = window.getMousePos() - previousMousePos;
    ball->velocity = dx;
    ball->move();
  }

} /* namespace gameplay */
} /* namespace billiards */
