/*
 * FanBatchRenderer.h
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#ifndef FANBATCHRENDERER_H_
#define FANBATCHRENDERER_H_

#include <AttribBuffer.h>
#include <IndexBuffer.h>
#include <Vertex.h>
#include <VertexArray.h>

namespace billiards { namespace graphics {

  class FanBatchRenderer
  {
    private:
      static constexpr unsigned int
      MAX_VERTICES                = 5000,
      MAX_INDICES                 = MAX_VERTICES + 1000,
      POSITION_FLOATS_PER_VERTEX  = 3,
      COLOR_FLOATS_PER_VERTEX     = 4
      ;

      static constexpr GLuint PRIMITIVE_RESTART_INDEX = MAX_INDICES;

      const ShaderProgram& shaderProgram;
      AttribBuffer posBuffer, colorBuffer;
      IndexBuffer indexBuffer;
      VertexArray vertexArray;

      GLfloat *positions, *colors;
      GLuint* indices;
      unsigned int iVertices, iIndices;
      GLuint indexNumber;

    public:
      FanBatchRenderer(const ShaderProgram& shaderProgram);
      ~FanBatchRenderer();

      void submit(const Fan& fan);
      void flush();
  };

} /* namespace graphics */
} /* namespace billiards */

#endif /* FANBATCHRENDERER_H_ */
