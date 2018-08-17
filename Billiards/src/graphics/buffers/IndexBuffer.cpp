/*
 * IndexBuffer.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <IndexBuffer.h>

namespace billiards { namespace graphics {

  IndexBuffer::IndexBuffer(GLuint* data, GLsizei indexCount, GLenum usage)
  : indexCount(indexCount)
  {
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), data, usage);
    unbind();
  }

  IndexBuffer::~IndexBuffer()
  {
  }

  void IndexBuffer::bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  }

  void IndexBuffer::unbind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

} /* namespace graphics */
} /* namespace billiards */
