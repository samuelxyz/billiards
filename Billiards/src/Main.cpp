/*
 * Main.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: Samuel Tan
 */

#include "Window.h"
#include "AttribBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "FanBatchRenderer.h"
#include "Mat4.h"

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

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    Vertex top   { Vec3(400.0f, 600.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) };
    Vertex left  { Vec3(166.7f, 200.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f) };
    Vertex right { Vec3(633.3f, 200.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f) };

    Fan triangle;
    triangle.push_back(top);
    triangle.push_back(left);
    triangle.push_back(right);
    fbr.submit(triangle);

    fbr.flush();

//    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
    glfwPollEvents();
  }

  return 0;
}
