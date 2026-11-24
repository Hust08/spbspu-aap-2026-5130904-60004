#pragma once
#include "shape.hpp"

namespace yapparov
{
    class Rectangle : public Shape
    {
    private:
        rectangle_t rect_;
    public:
        Rectangle(double width, double height, const point_t& pos);
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const point_t& p) override;
        void move(double x, double y) override;
        void scale(double k) override;
    };
}
