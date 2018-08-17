/*
 * AttribBuffer.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef ATTRIBBUFFER_H_
#define ATTRIBBUFFER_H_

#include <GLObject.h>

namespace billiards { namespace graphics {

  class AttribBuffer: public GLObject
  {
    private:
      GLuint numAttribComponents;

    public:
      AttribBuffer(GLfloat* data, GLuint numAttribComponents, GLsizei attribCount, GLenum usage);
      virtual ~AttribBuffer();

      virtual void bind() const override;
      virtual void unbind() const override;

      GLuint getNumAttribComponents() const { return numAttribComponents; }
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* ATTRIBBUFFER_H_ */
