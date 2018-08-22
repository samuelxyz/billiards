/*
 * FanBatchRenderer.cpp
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#include <FanBatchRenderer.h>
#include <ShaderProgram.h>

namespace billiards { namespace graphics {

  FanBatchRenderer::FanBatchRenderer(const ShaderProgram& shaderProgram)
  : shaderProgram(shaderProgram),
    posBuffer(nullptr, POSITION_FLOATS_PER_VERTEX, MAX_VERTICES, GL_STREAM_DRAW),
    colorBuffer(nullptr, COLOR_FLOATS_PER_VERTEX, MAX_VERTICES, GL_STREAM_DRAW),
    indexBuffer(nullptr, MAX_INDICES, GL_STREAM_DRAW),
    vertexArray(),
    positions(new GLfloat[MAX_VERTICES * POSITION_FLOATS_PER_VERTEX]),
    colors(new GLfloat[MAX_VERTICES * COLOR_FLOATS_PER_VERTEX]),
    indices(new GLuint[MAX_INDICES]),
    iVertices(0), iIndices(0),
    indexNumber(0)
  {
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(MAX_INDICES);

    vertexArray.addBuffer(posBuffer, shaderProgram, "position");
    vertexArray.addBuffer(colorBuffer, shaderProgram, "color");

    shaderProgram.bind();
    vertexArray.bind();
  }

  FanBatchRenderer::~FanBatchRenderer()
  {
    delete[] positions;
    delete[] colors;
    delete[] indices;
  }

  void FanBatchRenderer::submit(const Fan& fan)
  {
    if (iVertices + fan.size() >= MAX_VERTICES ||
        iIndices + fan.size() + 1 >= MAX_INDICES)
      return; // TODO better overflow handling

    for (const Vertex& vertex : fan)
    {
      unsigned int iPositions = iVertices * POSITION_FLOATS_PER_VERTEX;
      positions[iPositions + 0] = vertex.position.x;
      positions[iPositions + 1] = vertex.position.y;
      positions[iPositions + 2] = vertex.position.z;

      unsigned int iColors = iVertices * COLOR_FLOATS_PER_VERTEX;
      colors[iColors + 0] = vertex.color.x;
      colors[iColors + 1] = vertex.color.y;
      colors[iColors + 2] = vertex.color.z;
      colors[iColors + 3] = vertex.color.w;

      ++iVertices;

      indices[iIndices++] = indexNumber++;
    }

    // here is where iIndices and indexNumber diverge
    indices [iIndices++] = PRIMITIVE_RESTART_INDEX;
  }

  void FanBatchRenderer::flush()
  {
    // shouldn't need to fill rest of buffers with 0
    // because we only draw up to iIndices

    posBuffer.write(positions, iVertices);
    colorBuffer.write(colors, iVertices);
    indexBuffer.write(indices, iIndices);

//    // these will be necessary if ever using multiple renderers - consider unbinds too
//    shaderProgram.bind();
//    vertexArray.bind();

    indexBuffer.bind();
    glDrawElements(GL_TRIANGLE_FAN, iIndices, GL_UNSIGNED_INT, (void*) 0);

    iVertices = 0;
    iIndices = 0;
    indexNumber = 0;
  }

} /* namespace graphics */
} /* namespace billiards */
