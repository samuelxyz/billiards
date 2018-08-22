/*
 * Main.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: Samuel Tan
 */

#include "entity/Ball.h"
#include <FanBatchRenderer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Mat4.h>
#include <ShaderProgram.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Vertex.h>
#include <Window.h>
#include <vector>

int main()
{
  using namespace billiards;
  using namespace graphics;
  using namespace math;

  Window window;

  ShaderProgram shaderProgram("src/shaders/basic_vertex.glsl", "src/shaders/basic_fragment.glsl");
  Mat4 projMatrix = Mat4::ortho(0.0f, 800.0f, 0.0f, 800.0f);
  shaderProgram.setUniformMat4f("u_projMatrix", &projMatrix.elements[0]); // @suppress("Invalid arguments")

#if 0
  GLfloat positions[] =
  {
      166.7f, 200.0f,
      400.0f, 600.0f,
      633.3f, 200.0f
  };
  AttribBuffer positionBuffer(positions, 2, 3, GL_STATIC_DRAW);

  GLfloat colors[] =
  {
      1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f, 1.0f
  };
  AttribBuffer colorBuffer(colors, 4, 3, GL_STATIC_DRAW);

  VertexArray vertexArray;
  vertexArray.addBuffer(positionBuffer, shaderProgram, "position");
  vertexArray.addBuffer(colorBuffer, shaderProgram, "color");

  shaderProgram.bind();
  vertexArray.bind();
#endif

  FanBatchRenderer fbr(shaderProgram);
  entity::Ball ball(math::Vec2(400, 400), 30.0f, math::Vec4(1.0f, 0.8f, 0.6f, 1.0f));

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    ball.render(fbr);

    fbr.flush();

//    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
    glfwPollEvents();
  }

  return 0;
}
