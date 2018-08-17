/*
 * ShaderProgram.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <GLObject.h>
#include <string>
#include <unordered_map>

namespace billiards { namespace graphics {

  class ShaderProgram: public GLObject
  {
    private:
      std::unordered_map<std::string, GLint> uniformCache;

    public:
      ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
      virtual ~ShaderProgram();

      virtual void bind() const;
      virtual void unbind() const;

      GLint getAttribLocation(const char* attribName);
      void setUniformMat4f(const char* uniformName, GLfloat* matrixBegin);

    private:
      std::string loadFile(const std::string& filepath);
      GLuint compileShader(GLenum type, const std::string& source);
      GLint getUniformLocation(const std::string& uniformName);
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* SHADERPROGRAM_H_ */
