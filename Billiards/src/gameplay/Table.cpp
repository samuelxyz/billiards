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
    leftDrag { nullptr, math::Vec2(), math::Vec2() },
    rightDrag { false, math::Vec2() }
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
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      // drag balls around
      if (action == GLFW_PRESS && leftDrag.target == nullptr)
      {
        math::Vec2 clickPos = window.getMousePos();
        for (entity::Ball* b : ballList)
        {
          if (b->containsPoint(clickPos))
          {
            leftDrag.previousMousePos = clickPos;
            leftDrag.idealBallOffset = b->position - clickPos;
            leftDrag.target = b;
            b->beingDragged = true;
            break;
          }
        }
      }
      else if (action == GLFW_RELEASE && leftDrag.target != nullptr)
      {
        leftDrag.target->beingDragged = false;
        leftDrag.target = nullptr;
      }
    } // if (button == GLFW_MOUSE_BUTTON_LEFT)
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      // control gravity
      if (action == GLFW_PRESS && !rightDrag.active)
      {
        rightDrag.active = true;
        rightDrag.originalPos = window.getMousePos();
      }
      else if (action == GLFW_RELEASE && rightDrag.active)
      {
        rightDrag.active = false;
      }
    }
  }

  void Table::checkDrag()
  {
    if (leftDrag.target)
      drag(leftDrag.target);
    if (rightDrag.active)
      drag(stats.gravity);
  }

  void Table::drag(entity::Ball* ball)
  {
    math::Vec2 currentMousePos = window.getMousePos();
    math::Vec2 dx = currentMousePos - leftDrag.previousMousePos;

    math::Vec2 springDX = (currentMousePos + leftDrag.idealBallOffset) - ball->position;
    math::Vec2 springForce = springDX / 6;

    ball->velocity = dx + springForce;
    ball->move();

    leftDrag.previousMousePos = currentMousePos;
  }

  void Table::drag(math::Vec2& target, float sensitivity)
  {
    target = (window.getMousePos() - rightDrag.originalPos) * sensitivity;
  }

} /* namespace gameplay */
} /* namespace billiards */
