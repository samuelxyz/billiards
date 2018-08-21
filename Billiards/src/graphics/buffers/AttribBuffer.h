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
      unsigned int numAttribComponents;

    public:
      AttribBuffer(GLfloat* data, unsigned int numAttribComponents, unsigned int attribCount, GLenum usage);
      virtual ~AttribBuffer();

      virtual void bind() const override;
      virtual void unbind() const override;

      void write(GLfloat* data, unsigned int attribCount) const;

      unsigned int getNumAttribComponents() const { return numAttribComponents; }
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* ATTRIBBUFFER_H_ */
