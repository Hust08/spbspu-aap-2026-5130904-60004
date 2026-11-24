#include "polygon.hpp"
#include <algorithm>
#include <stdexcept>

namespace yapparov
{
    Polygon::Polygon(const point_t* ver, int size)
    {
        if (size < 3 || ver == nullptr)
        {
            throw std::invalid_argument("invalid polygon");
        }
        size_ = size;
        ver_ = new point_t[size_];
        double sum = 0;
        double cx = 0;
        double cy = 0;
        for (int i = 0; i < size_; i++)
        {
            ver_[i] = ver[i];
            int j = (i + 1) % size_;
            double s = ver[i].x * ver[j].y - ver[j].x * ver[i].y;
            sum += s;
            cx += (ver[i].x + ver[j].x) * s;
            cy += (ver[i].y + ver[j].y) * s;
        }
        if (sum == 0)
        {
            delete[] ver_;
            throw std::invalid_argument("zero area");
        }
        cent_.x = cx / (3 * sum);
        cent_.y = cy / (3 * sum);
    }

    Polygon::Polygon(const Polygon& p) :
        cent_(p.cent_),
        ver_(new point_t[p.size_]),
        size_(p.size_)
    {
        for (int i = 0; i < size_; i++)
        {
            ver_[i] = p.ver_[i];
        }
    }
    Polygon::Polygon(Polygon&& p) noexcept :
        cent_(p.cent_),
        ver_(p.ver_),
        size_(p.size_)
    {
        p.ver_ = nullptr;
        p.size_ = 0;
    }

    Polygon& Polygon::operator=(const Polygon& p)
    {
        if (this != &p)
        {
            point_t* newVer = new point_t[p.size_];
            for (int i = 0; i < p.size_; i++)
            {
                newVer[i] = p.ver_[i];
            }
            delete[] ver_;
            ver_ = newVer;
            size_ = p.size_;
            cent_ = p.cent_;
        }
        return *this;
    }

    Polygon& Polygon::operator=(Polygon&& p) noexcept
    {
        if (this != &p)
        {
            delete[] ver_;
            ver_ = p.ver_;
            size_ = p.size_;
            cent_ = p.cent_;
            p.ver_ = nullptr;
            p.size_ = 0;
        }
        return *this;
    }
    Polygon::~Polygon()
    {
        delete[] ver_;
    }
    double Polygon::getArea() const
    {
        double sum = 0;
        for (int i = 0; i < size_; i++)
        {
            int j = (i + 1) % size_;
            sum += ver_[i].x * ver_[j].y
                - ver_[j].x * ver_[i].y;
        }
        if (sum < 0)
        {
            sum = -sum;
        }
        return sum / 2;
    }

    rectangle_t Polygon::getFrameRect() const
    {
        double minX = ver_[0].x;
        double maxX = ver_[0].x;
        double minY = ver_[0].y;
        double maxY = ver_[0].y;
        for (int i = 1; i < size_; i++)
        {
            minX = std::min(minX, ver_[i].x);
            maxX = std::max(maxX, ver_[i].x);
            minY = std::min(minY, ver_[i].y);
            maxY = std::max(maxY, ver_[i].y);
        }
        rectangle_t rect;
        rect.width = maxX - minX;
        rect.height = maxY - minY;
        rect.pos.x = (minX + maxX) / 2.0;
        rect.pos.y = (minY + maxY) / 2.0;
        return rect;
    }

    void Polygon::move(const point_t& p)
    {
        move(p.x - cent_.x, p.y - cent_.y);
    }

    void Polygon::move(double x, double y)
    {
        for (int i = 0; i < size_; i++)
        {
            ver_[i].x += x;
            ver_[i].y += y;
        }
        cent_.x += x;
        cent_.y += y;
    }

    void Polygon::scale(double k)
    {
        for (int i = 0; i < size_; i++)
        {
            ver_[i].x = cent_.x + (ver_[i].x - cent_.x) * k;
            ver_[i].y = cent_.y + (ver_[i].y - cent_.y) * k;
        }
    }
}
