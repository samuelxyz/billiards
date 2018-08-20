/*
 * AttribBuffer.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <AttribBuffer.h>

namespace billiards
{
  namespace graphics
  {

    AttribBuffer::AttribBuffer(GLfloat* data, GLuint numAttribComponents,
        GLsizei attribCount, GLenum usage)
    : numAttribComponents(numAttribComponents)
    {
      glGenBuffers(1, &ID);
      bind();
      glBufferData(GL_ARRAY_BUFFER, attribCount * numAttribComponents * sizeof(GLfloat), data, usage);
      unbind();
    }

    AttribBuffer::~AttribBuffer()
    {
      glDeleteBuffers(1, &ID);
    }

    void AttribBuffer::bind() const
    {
      glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void AttribBuffer::unbind() const
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

  } /* namespace graphics */
} /* namespace billiards */
