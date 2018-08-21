/*
 * IndexBuffer.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <IndexBuffer.h>

namespace billiards { namespace graphics {

  IndexBuffer::IndexBuffer(GLuint* data, unsigned int indexCount, GLenum usage)
  : indexCount(indexCount)
  {
    glGenBuffers(1, &ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), data, usage);
    unbind();
  }

  IndexBuffer::~IndexBuffer()
  {
    glDeleteBuffers(1, &ID);
  }

  void IndexBuffer::bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  }

  void IndexBuffer::unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void IndexBuffer::write(GLuint* data, unsigned int indexCount) const
  {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexCount * sizeof(GLuint), data);
    unbind();
  }

} /* namespace graphics */
} /* namespace billiards */
