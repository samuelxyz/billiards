/*
 * Vertex.h
 *
 *  Created on: Aug 20, 2018
 *      Author: Samuel Tan
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <Vec3.h>
#include <Vec4.h>
#include <vector>

namespace billiards { namespace graphics {

  struct Vertex
  {
    public:
      math::Vec3 position;
      math::Vec4 color;

      Vertex(const math::Vec3& position, const math::Vec4& color);
  };

  typedef std::vector<Vertex> Fan;

} /* namespace graphics */
} /* namespace billiards */

#endif /* VERTEX_H_ */
