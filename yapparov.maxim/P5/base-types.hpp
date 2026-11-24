#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace yapparov
{
  class point_t
  {
  public:
    double x, y;
  };
  class rectangle_t
  {
  public:
    double width, height;
    point_t pos;
  };
}

#endif
