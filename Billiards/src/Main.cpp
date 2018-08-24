/*
 * Main.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: Samuel Tan
 */

#include <Ball.h>
#include <FanBatchRenderer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Mat4.h>
#include <ShaderProgram.h>
#include <Table.h>
#include <Vec2.h>
#include <Vec4.h>
#include <Window.h>

int main()
{
  using namespace billiards;
  using namespace graphics;
  using namespace math;

  Window window;

  ShaderProgram shaderProgram("src/shaders/basic_vertex.glsl", "src/shaders/basic_fragment.glsl");
  Mat4 projMatrix = Mat4::ortho(0.0f, 800.0f, 0.0f, 800.0f);
  shaderProgram.setUniformMat4f("u_projMatrix", &projMatrix.elements[0]); // @suppress("Invalid arguments")

  FanBatchRenderer fbr(shaderProgram);
  gameplay::Table table(window);
  window.bindTable(&table);
  table.add(new entity::Ball(table, math::Vec2(400, 400), math::Vec2(), 30.0f, 10.0f, math::Vec4(1.0f, 0.8f, 0.6f, 1.0f)));
  table.add(new entity::Ball(table, math::Vec2(100, 420), math::Vec2(2.0f, -2.0f/30), 40.0f, 60.0f, math::Vec4(0.6f, 1.0f, 0.5f, 1.0f)));
  table.add(new entity::Ball(table, math::Vec2(400, 200), math::Vec2(0.5f, 3.0f), 30.0f, 20.0f, math::Vec4(0.3f, 0.6f, 0.8f, 1.0f)));

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    table.update();
    table.render(fbr);

    fbr.flush();

    window.swapBuffers();
    glfwPollEvents();
  }

  return 0;
}
