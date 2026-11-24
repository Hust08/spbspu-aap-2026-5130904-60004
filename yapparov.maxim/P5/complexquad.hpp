#ifndef COMPLEXQUAD_HPP
#define COMPLEXQUAD_HPP
#include "shape.hpp"

namespace yapparov
{
  class Complexquad: public Shape
  {
  private:
    point_t ver_[4];
    point_t cent_;
  public:
    Complexquad(const point_t& a, const point_t& b, const point_t& c, const point_t& d);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double x, double y) override;
    void scale(double k) override;
  };
}

#endif
