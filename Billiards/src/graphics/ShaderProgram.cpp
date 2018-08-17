/*
 * ShaderProgram.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <GL/glew.h>
#include <ShaderProgram.h>

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

namespace billiards { namespace graphics {

  ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
  {
    ID = glCreateProgram();

    GLuint vertexID = compileShader(GL_VERTEX_SHADER, loadFile(vertexPath));
    GLuint fragmentID = compileShader(GL_FRAGMENT_SHADER, loadFile(fragmentPath));

    assert(vertexID != 0 && fragmentID != 0);

    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);
    glValidateProgram(ID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
  }

  ShaderProgram::~ShaderProgram()
  {
    glDeleteProgram(ID);
  }

  void ShaderProgram::bind() const
  {
    glUseProgram(ID);
  }

  void ShaderProgram::unbind() const
  {
  }

  std::string ShaderProgram::loadFile(const std::string& filepath)
  {
    std::ifstream fstream(filepath);
    std::stringstream sstream;
    std::string line;

    while (getline(fstream, line))
    {
      sstream << line << "\n";
    }

    return sstream.str();
  }

    void ShaderProgram::setUniformMat4f(const char* uniformName,
        GLfloat* matrixBegin)
    {
      bind();
      glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, matrixBegin);
    }

  GLuint ShaderProgram::compileShader(GLenum type, const std::string& source)
  {
    GLuint shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // error handling
        int compileSuccess;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE)
        {
          int length;
          glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

          char* msg = new char[length];
          glGetShaderInfoLog(shader, length, &length, msg);
          std::cerr << "Failed to compile " << ((type == GL_VERTEX_SHADER) ?
              "vertex" : "fragment") << " shader!" << std::endl;
          std::cerr << msg << std::endl;

          delete msg;

          glDeleteShader(shader);
          return 0;
        }

        return shader;
  }

    GLint ShaderProgram::getAttribLocation(const char* attribName)
    {
      return glGetAttribLocation(ID, attribName);
    }

    GLint ShaderProgram::getUniformLocation(const std::string& uniformName)
    {
      auto cachedLoc = uniformCache.find(uniformName);

      GLint location;

      if (cachedLoc == uniformCache.end())
      {
        location = glGetUniformLocation(ID, uniformName.c_str());
        uniformCache[uniformName] = location;
      }
      else
      {
        location = uniformCache[uniformName];
      }

      return location;
    }

} /* namespace graphics */
} /* namespace billiards */
