#include "complexquad.hpp"
#include <stdexcept>

namespace yapparov
{
  const int ver_count = 4;
  const double half = 2.0;

  Complexquad::Complexquad(const point_t& a, const point_t& b, const point_t& c, const point_t& d)
  {
    ver_[0] = a;
    ver_[1] = b;
    ver_[2] = c;
    ver_[3] = d;
    cent_.x = (a.x + b.x + c.x + d.x) / ver_count;
    cent_.y = (a.y + b.y + c.y + d.y) / ver_count;
  }

  double Complexquad::getArea() const
  {
    double sum = 0.0;

    for (int i = 0; i < ver_count; i++)
    {
      const int next = (i + 1) % ver_count;
      sum += ver_[i].x * ver_[next].y - ver_[next].x * ver_[i].y;
    }
    if (sum < 0.0)
    {
      sum = -sum;
    }

    return sum / half;
  }

  rectangle_t Complexquad::getFrameRect() const
  {
    double min_x = ver_[0].x;
    double max_x = ver_[0].x;
    double min_y = ver_[0].y;
    double max_y = ver_[0].y;
    for (int i = 1; i < ver_count; i++)
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

  void Complexquad::move(const point_t& p)
  {
    const double dx = p.x - cent_.x;
    const double dy = p.y - cent_.y;
    move(dx, dy);
  }

  void Complexquad::move(double x, double y)
  {
    for (int i = 0; i < ver_count; i++)
    {
      ver_[i].x += x;
      ver_[i].y += y;
    }

    cent_.x += x;
    cent_.y += y;
  }

  void Complexquad::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("invalid scale");
    }

    for (int i = 0; i < ver_count; i++)
    {
      ver_[i].x = cent_.x + (ver_[i].x - cent_.x) * k;
      ver_[i].y = cent_.y + (ver_[i].y - cent_.y) * k;
    }
  }
}
