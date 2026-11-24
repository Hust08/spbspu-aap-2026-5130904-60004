#include "complexquad.hpp"
#include <algorithm>

namespace yapparov
{
    Complexquad::Complexquad(const point_t& a, const point_t& b, const point_t& c, const point_t& d)
    {
        v_[0] = a;
        v_[1] = b;
        v_[2] = c;
        v_[3] = d;
        double x1 = b.x - a.x;
        double y1 = b.y - a.y;
        double x2 = d.x - c.x;
        double y2 = d.y - c.y;
        double t = ((c.x - a.x) * y2 - (c.y - a.y) * x2) / (x1 * y2 - y1 * x2);
        c_.x = a.x + t * x1;
        c_.y = a.y + t * y1;
    }

    double Complexquad::getArea() const
    {
        double s1 = (v_[1].x - c_.x) * (v_[2].y - c_.y) - (v_[2].x - c_.x) * (v_[1].y - c_.y);
        if (s1 < 0)
        {
            s1 = -s1;
        }
        s1 = s1 / 2.0;
        double s2 = (v_[3].x - c_.x) * (v_[0].y - c_.y) - (v_[0].x - c_.x) * (v_[3].y - c_.y);
        if (s2 < 0)
        {
            s2 = -s2;
        }
        s2 = s2 / 2.0;
        return s1 + s2;
    }

    rectangle_t Complexquad::getFrameRect() const
    {
        double minX = v_[0].x;
        double maxX = v_[0].x;
        double minY = v_[0].y;
        double maxY = v_[0].y;
        for (int i = 1; i < 4; i++)
        {
            minX = std::min(minX, v_[i].x);
            maxX = std::max(maxX, v_[i].x);
            minY = std::min(minY, v_[i].y);
            maxY = std::max(maxY, v_[i].y);
        }
        rectangle_t rect;
        rect.width = maxX - minX;
        rect.height = maxY - minY;
        rect.pos.x = (minX + maxX) / 2.0;
        rect.pos.y = (minY + maxY) / 2.0;
        return rect;
    }

    void Complexquad::move(const point_t& p)
    {
        double dx = p.x - c_.x;
        double dy = p.y - c_.y;
        move(dx, dy);
    }

    void Complexquad::move(double dx, double dy)
    {
        for (int i = 0; i < 4; i++)
        {
            v_[i].x += dx;
            v_[i].y += dy;
        }
        c_.x += dx;
        c_.y += dy;
    }

    void Complexquad::scale(double k)
    {
        for (int i = 0; i < 4; i++)
        {
            v_[i].x = c_.x + (v_[i].x - c_.x) * k;
            v_[i].y = c_.y + (v_[i].y - c_.y) * k;
        }
    }
}
