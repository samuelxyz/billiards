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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
  using namespace billiards;
  using namespace graphics;

  Window window;

  ShaderProgram shaderProgram("src/shaders/basic_vertex.glsl", "src/shaders/basic_fragment.glsl");
  glm::mat4 projMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);
  shaderProgram.setUniformMat4f("u_projMatrix", &projMatrix[0][0]); // @suppress("Invalid arguments")

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

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.swapBuffers();
    glfwPollEvents();
  }

  return 0;
}
