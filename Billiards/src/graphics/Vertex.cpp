/*
 * Vertex.cpp
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#include <Vertex.h>

namespace billiards { namespace graphics {

  Vertex::Vertex(const math::Vec3& position, const math::Vec4& color)
  : position(position), color(color)
  {
  }

} /* namespace graphics */
} /* namespace billiards */
