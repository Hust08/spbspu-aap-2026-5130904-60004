#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "shape.hpp"

namespace yapparov
{
  class Polygon: public Shape
  {
  private:
    point_t cent_;
    point_t* ver_;
    int size_;
  public:
    Polygon(const point_t* ver, int size);
    Polygon(const Polygon& p);
    Polygon(Polygon&& p) noexcept;
    ~Polygon() override;
    Polygon& operator=(const Polygon& p);
    Polygon& operator=(Polygon&& p) noexcept;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double x, double y) override;
    void scale(double k) override;
  };
}

#endif
