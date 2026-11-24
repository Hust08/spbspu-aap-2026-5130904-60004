#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "complexquad.hpp"
#include "polygon.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

namespace yapparov
{
  const double half = 2.0;
  const double rect_width = 4.0;
  const double rect_height = 2.0;
  const int poly_count = 5;
  const int max_coord = 5;

  void scaleShapes(Shape** shapes, int count, const point_t& p, double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("invalid k");
    }
    for (int i = 0; i < count; i++)
    {
      const point_t old = shapes[i]->getFrameRect().pos;
      shapes[i]->move(p);
      const point_t now = shapes[i]->getFrameRect().pos;
      shapes[i]->scale(k);
      shapes[i]->move((old.x - now.x) * k, (old.y - now.y) * k);
    }
  }

  rectangle_t totalFrame(Shape** shapes, int count)
  {
    const rectangle_t first = shapes[0]->getFrameRect();
    double min_x = first.pos.x - first.width / half;
    double max_x = first.pos.x + first.width / half;
    double min_y = first.pos.y - first.height / half;
    double max_y = first.pos.y + first.height / half;

    for (int i = 1; i < count; i++)
    {
      const rectangle_t r = shapes[i]->getFrameRect();
      min_x = std::min(min_x, r.pos.x - r.width / half);
      max_x = std::max(max_x, r.pos.x + r.width / half);
      min_y = std::min(min_y, r.pos.y - r.height / half);
      max_y = std::max(max_y, r.pos.y + r.height / half);
    }

    rectangle_t rect;
    rect.width = max_x - min_x;
    rect.height = max_y - min_y;
    rect.pos.x = (min_x + max_x) / half;
    rect.pos.y = (min_y + max_y) / half;
    return rect;
  }

  void showInfo(Shape** shapes, const char** fig_names, int count)
  {
    double total_area = 0.0;
    for (int i = 0; i < count; i++)
    {
      const rectangle_t r = shapes[i]->getFrameRect();
      const double area = shapes[i]->getArea();
      total_area += area;
      std::cout << fig_names[i] << ": area = " << area << ", width = " << r.width << ", height = " << r.height
                << ", center = (" << r.pos.x << ", " << r.pos.y << ")\n";
    }
    const rectangle_t r = totalFrame(shapes, count);
    std::cout << "Total area: " << total_area << "\n";
    std::cout << "Total frame: width = " << r.width << ", height = " << r.height << ", center = (" << r.pos.x << ", "
              << r.pos.y << ")\n";
  }
}

int main()
{
  using namespace yapparov;
  const point_t poly[poly_count] = {{0, 0}, {4, 0}, {4, 3}, {2, 5}, {0, 3}};
  point_t rect_pos;
  rect_pos.x = 0.0;
  rect_pos.y = 0.0;
  point_t a;
  a.x = 1;
  a.y = 1;
  point_t b;
  b.x = max_coord;
  b.y = max_coord;
  point_t c;
  c.x = max_coord;
  c.y = 1;
  point_t d;
  d.x = 1;
  d.y = max_coord;

  try
  {
    Rectangle rect(rect_width, rect_height, rect_pos);
    Complexquad quad(a, b, c, d);
    Polygon polygon(poly, poly_count);
    const int count = 3;
    Shape* shapes[count];
    shapes[0] = &rect;
    shapes[1] = &quad;
    shapes[2] = &polygon;
    const char* fig_names[count];
    fig_names[0] = "Rectangle";
    fig_names[1] = "Complexquad";
    fig_names[2] = "Polygon";
    std::cout << "Before:\n";
    showInfo(shapes, fig_names, count);
    point_t p;
    double k = 0.0;
    std::cout << "\n";
    if (!(std::cin >> p.x >> p.y >> k))
    {
      throw std::invalid_argument("invalid input");
    }
    scaleShapes(shapes, count, p, k);
    std::cout << "\nAfter:\n";
    showInfo(shapes, fig_names, count);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
