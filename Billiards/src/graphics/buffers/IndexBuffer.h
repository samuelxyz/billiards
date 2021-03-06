/*
 * IndexBuffer.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <GLObject.h>

namespace billiards { namespace graphics {

  class IndexBuffer: public GLObject
  {
    private:
      GLsizei indexCount;

    public:
      IndexBuffer(GLuint* data, unsigned int indexCount, GLenum usage);
      virtual ~IndexBuffer();

      virtual void bind() const override;
      virtual void unbind() const override;

      void write(GLuint* data, unsigned int indexCount) const;
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* INDEXBUFFER_H_ */
