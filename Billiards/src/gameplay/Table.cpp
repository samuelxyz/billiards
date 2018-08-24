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
    dragging { nullptr, math::Vec2(), math::Vec2() }
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
    if (action == GLFW_PRESS && dragging.target == nullptr)
    {
      math::Vec2 clickPos = window.getMousePos();
      for (entity::Ball* b : ballList)
      {
        if (b->containsPoint(clickPos))
        {
          dragging.previousMousePos = clickPos;
          dragging.idealBallOffset = b->position - clickPos;
          dragging.target = b;
          b->beingDragged = true;
          break;
        }
      }
    }

    else if (action == GLFW_RELEASE && dragging.target != nullptr)
    {
      dragging.target->beingDragged = false;
      dragging.target = nullptr;
    }
  }

  void Table::checkDrag()
  {
    if (dragging.target)
      drag(dragging.target);
  }

  void Table::drag(entity::Ball* ball)
  {
    math::Vec2 currentMousePos = window.getMousePos();
    math::Vec2 dx = currentMousePos - dragging.previousMousePos;

    math::Vec2 springDX = (currentMousePos + dragging.idealBallOffset) - ball->position;
    math::Vec2 springForce = springDX / 6;

    ball->velocity = dx + springForce;
    ball->move();

    dragging.previousMousePos = currentMousePos;
  }

} /* namespace gameplay */
} /* namespace billiards */
