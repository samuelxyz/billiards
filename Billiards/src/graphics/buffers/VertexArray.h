/*
 * VertexArray.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include <GLObject.h>

namespace billiards { namespace graphics {

  class AttribBuffer;
  class ShaderProgram;

  class VertexArray: public GLObject
  {
    public:
      VertexArray();
      virtual ~VertexArray();

      void addBuffer(const AttribBuffer& buffer, const ShaderProgram& relevantProgram, const char* attribName);
      virtual void bind() const override;
      virtual void unbind() const override;
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* VERTEXARRAY_H_ */
