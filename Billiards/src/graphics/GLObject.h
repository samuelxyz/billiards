/*
 * GLObject.h
 *
 *  Created on: Aug 17, 2018
 *      Author: Samuel Tan
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_

#include <GL/glew.h>

namespace billiards { namespace graphics {

  class GLObject
  {
    protected:
      GLuint ID;

    public:
      GLObject(): ID(0) {};
      virtual ~GLObject() {};

      virtual void bind() const = 0;
      virtual void unbind() const = 0;
  };

} }

#endif /* GLOBJECT_H_ */
