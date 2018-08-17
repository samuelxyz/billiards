/*
 * VertexArray.cpp
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#include <VertexArray.h>
#include <AttribBuffer.h>
#include <ShaderProgram.h>

namespace billiards
{
  namespace graphics
  {

    VertexArray::VertexArray()
    {
      glGenVertexArrays(1, &ID);
    }

    VertexArray::~VertexArray()
    {
    }

    void VertexArray::addBuffer(AttribBuffer& buffer, ShaderProgram& relevantProgram, const char* attribName)
    {
      bind();
      buffer.bind();

      GLuint attribLocation = relevantProgram.getAttribLocation(attribName);
      glEnableVertexAttribArray(attribLocation);
      glVertexAttribPointer(attribLocation, buffer.getNumAttribComponents(), GL_FLOAT, GL_FALSE, 0, 0);

      buffer.unbind();
      unbind();
    }

    void VertexArray::bind() const
    {
      glBindVertexArray(ID);
    }

    void VertexArray::unbind() const
    {
      glBindVertexArray(0);
    }

  } /* namespace graphics */
} /* namespace billiards */
