/*
 * Window.h
 *
 *  Created on: Aug 16, 2018
 *      Author: Samuel Tan
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace billiards
{
  namespace math
  {
    struct Vec2;
  } /* namespace math */

  namespace gameplay
  {
    class Table;
  }
} /* namespace billiards */

namespace billiards { namespace graphics {

  class Window
  {
    public:
      Window();
      virtual ~Window();

      bool shouldClose() const;
      void swapBuffers() const;

      static void printGLFWError(int error, const char* description);
      static void APIENTRY printGLDebug(GLenum source, GLenum type, GLuint id,
            GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

      static void handleKey(GLFWwindow*, int key, int scancode, int action, int mods);
      static void handleMouseButton(GLFWwindow*, int button, int action, int mods);
      math::Vec2 getMousePos() const;

      void bindTable(gameplay::Table* table);

    private:
      GLFWwindow* glfwWindow;
      gameplay::Table* table;

      static Window* getWindow(GLFWwindow*); // from window user pointer

  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* WINDOW_H_ */
