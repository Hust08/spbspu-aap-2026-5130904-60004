#include "polygon.hpp"
#include <stdexcept>

namespace yapparov
{
  const double half = 2.0;

  Polygon::Polygon(const point_t* ver, int size)
  {
    if (ver == nullptr || size < 3)
    {
      throw std::invalid_argument("invalid polygon");
    }
    size_ = size;
    ver_ = new point_t[size_];
    cent_.x = 0.0;
    cent_.y = 0.0;
    for (int i = 0; i < size_; i++)
    {
      ver_[i] = ver[i];
      cent_.x += ver[i].x;
      cent_.y += ver[i].y;
    }
    cent_.x /= size_;
    cent_.y /= size_;
  }

  Polygon::Polygon(const Polygon& p)
  {
    size_ = p.size_;
    ver_ = new point_t[size_];
    for (int i = 0; i < size_; i++)
    {
      ver_[i] = p.ver_[i];
    }
    cent_.x = p.cent_.x;
    cent_.y = p.cent_.y;
  }

  Polygon::Polygon(Polygon&& p) noexcept
  {
    ver_ = p.ver_;
    size_ = p.size_;
    cent_.x = p.cent_.x;
    cent_.y = p.cent_.y;
    p.ver_ = nullptr;
    p.size_ = 0;
    p.cent_.x = 0.0;
    p.cent_.y = 0.0;
  }

  Polygon::~Polygon()
  {
    delete[] ver_;
  }

  Polygon& Polygon::operator=(const Polygon& p)
  {
    if (this != &p)
    {
      point_t* const new_ver = new point_t[p.size_];
      for (int i = 0; i < p.size_; i++)
      {
        new_ver[i] = p.ver_[i];
      }
      delete[] ver_;
      ver_ = new_ver;
      size_ = p.size_;
      cent_.x = p.cent_.x;
      cent_.y = p.cent_.y;
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
      cent_.x = p.cent_.x;
      cent_.y = p.cent_.y;
      p.ver_ = nullptr;
      p.size_ = 0;
      p.cent_.x = 0.0;
      p.cent_.y = 0.0;
    }
    return *this;
  }

  double Polygon::getArea() const
  {
    double sum = 0.0;
    for (int i = 0; i < size_; i++)
    {
      const int next = (i + 1) % size_;
      sum += ver_[i].x * ver_[next].y - ver_[next].x * ver_[i].y;
    }
    if (sum < 0.0)
    {
      sum = -sum;
    }
    return sum / half;
  }

  rectangle_t Polygon::getFrameRect() const
  {
    double min_x = ver_[0].x;
    double max_x = ver_[0].x;
    double min_y = ver_[0].y;
    double max_y = ver_[0].y;
    for (int i = 1; i < size_; i++)
    {
      if (ver_[i].x < min_x)
      {
        min_x = ver_[i].x;
      }
      if (ver_[i].x > max_x)
      {
        max_x = ver_[i].x;
      }
      if (ver_[i].y < min_y)
      {
        min_y = ver_[i].y;
      }
      if (ver_[i].y > max_y)
      {
        max_y = ver_[i].y;
      }
    }
    rectangle_t rect;
    rect.width = max_x - min_x;
    rect.height = max_y - min_y;
    rect.pos.x = (min_x + max_x) / half;
    rect.pos.y = (min_y + max_y) / half;
    return rect;
  }

  void Polygon::move(const point_t& p)
  {
    const double dx = p.x - cent_.x;
    const double dy = p.y - cent_.y;
    move(dx, dy);
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
    if (k <= 0.0)
    {
      throw std::invalid_argument("invalid scale");
    }
    for (int i = 0; i < size_; i++)
    {
      ver_[i].x = cent_.x + (ver_[i].x - cent_.x) * k;
      ver_[i].y = cent_.y + (ver_[i].y - cent_.y) * k;
    }
  }
}
