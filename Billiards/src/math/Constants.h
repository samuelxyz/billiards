/*
 * Constants.h
 *
 *  Created on: Aug 21, 2018
 *      Author: Samuel Tan
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace billiards
{
  struct Constants
  {
      static constexpr float
      PI        = 3.14159265,
      TWO_PI    = 6.28318531,
      HALF_PI   = 1.57079633;

      static constexpr int
      TABLE_PANE_HEIGHT = 800,
      TABLE_PANE_WIDTH  = 800;
  };

}

#endif /* CONSTANTS_H_ */
