/*
 * Main.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: Samuel Tan
 */

#include "Window.h"

int main()
{
  using namespace billiards;

  graphics::Window window;

  while (!window.shouldClose())
  {
    // TODO render here

    window.swapBuffers();
    glfwPollEvents();
  }

  return 0;
}
