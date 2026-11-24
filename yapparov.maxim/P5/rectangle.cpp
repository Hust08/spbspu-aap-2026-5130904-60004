#include "rectangle.hpp"
#include <stdexcept>

namespace yapparov
{
    Rectangle::Rectangle(double width, double height, const point_t& center)
    {
        if (width <= 0.0 || height <= 0.0)
        {
            throw std::invalid_argument("invalid rectangle");
        }
        width_ = width;
        height_ = height;
        cent_ = center;
    }

    double Rectangle::getArea() const
    {
        return width_ * height_;
    }

    rectangle_t Rectangle::getFrameRect() const
    {
        rectangle_t rect;
        rect.width = width_;
        rect.height = height_;
        rect.pos = cent_;
        return rect;
    }

    void Rectangle::move(const point_t& p)
    {
        cent_ = p;
    }

    void Rectangle::move(double x, double y)
    {
        cent_.x += x;
        cent_.y += y;
    }

    void Rectangle::scale(double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("invalid scale");
        }
        width_ *= k;
        height_ *= k;
    }
}
