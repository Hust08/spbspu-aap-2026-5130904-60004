#include "rectangle.hpp"
#include <stdexcept>

namespace yapparov
{
    Rectangle::Rectangle(double width, double height, const point_t& pos) :
        rect_{width, height, pos}
    {
        if (width <= 0.0 || height <= 0.0)
        {
            throw std::invalid_argument("width and height > 0");
        }
    }

    double Rectangle::getArea() const
    {
        return rect_.width * rect_.height;
    }

    rectangle_t Rectangle::getFrameRect() const
    {
        return rect_;
    }

    void Rectangle::move(const point_t& p)
    {
        rect_.pos = p;
    }

    void Rectangle::move(double x, double y)
    {
        rect_.pos.x += x;
        rect_.pos.y += y;
    }

    void Rectangle::scale(double k)
    {
        if (k <= 0.0)
        {
            throw std::invalid_argument("k>0");
        }
        rect_.width *= k;
        rect_.height *= k;
    }
}
