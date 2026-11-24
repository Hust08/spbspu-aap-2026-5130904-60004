#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace yapparov
{
  class Rectangle: public Shape
  {
  private:
    double width_;
    double height_;
    point_t cent_;
  public:
    Rectangle(double width, double height, const point_t& cent);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double x, double y) override;
    void scale(double k) override;
  };
}

#endif
