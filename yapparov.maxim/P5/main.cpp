
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
        rectangle_t first = shapes[0]->getFrameRect();
        double min_x = first.pos.x - first.width / 2.0;
        double max_x = first.pos.x + first.width / 2.0;
        double min_y = first.pos.y - first.height / 2.0;
        double max_y = first.pos.y + first.height / 2.0;

        for (int i = 1; i < count; i++)
        {
            const rectangle_t r = shapes[i]->getFrameRect();
            min_x = std::min(min_x, r.pos.x - r.width / 2.0);
            max_x = std::max(max_x, r.pos.x + r.width / 2.0);
            min_y = std::min(min_y, r.pos.y - r.height / 2.0);
            max_y = std::max(max_y, r.pos.y + r.height / 2.0);
        }

        rectangle_t rect;
        rect.width = max_x - min_x;
        rect.height = max_y - min_y;
        rect.pos.x = (min_x + max_x) / 2.0;
        rect.pos.y = (min_y + max_y) / 2.0;
        return rect;
    }

    void showInfo(Shape** shapes, const char** names, int count)
    {
        double total = 0.0;

        for (int i = 0; i < count; i++)
        {
            const rectangle_t r = shapes[i]->getFrameRect();
            const double area = shapes[i]->getArea();
            total += area;

            std::cout << names[i] << ": area = " << area
                << ", width = " << r.width
                << ", height = " << r.height
                << ", center = (" << r.pos.x << ", "
                << r.pos.y << ")\n";
        }

        const rectangle_t r = totalFrame(shapes, count);
        std::cout << "Total area: " << total << "\n";
        std::cout << "Total frame: width = " << r.width
            << ", height = " << r.height
            << ", center = (" << r.pos.x << ", "
            << r.pos.y << ")\n";
    }
}

int main()
{
    using namespace yapparov;

    const point_t fiveSidedPolygon[] = {
        {0, 0}, {4, 0}, {4, 3}, {2, 5}, {0, 3}
    };

    try
    {
        Rectangle rect(4.0, 2.0, {0.0, 0.0});
        Complexquad quad({1, 1}, {5, 5}, {5, 1}, {1, 5});
        Polygon poly(fiveSidedPolygon, 5);

        const int shape_count = 3;
        Shape* shapes[shape_count] = { &rect, &quad, &poly };
        const char* names[shape_count] = {
            "Rectangle", "Complexquad", "Polygon"
        };

        std::cout << "Before:\n";
        showInfo(shapes, names, shape_count);

        point_t p{};
        double k = 0.0;

        std::cout << "\n";
        if (!(std::cin >> p.x >> p.y >> k))
        {
            throw std::invalid_argument("invalid input");
        }

        scaleShapes(shapes, shape_count, p, k);

        std::cout << "\nAfter:\n";
        showInfo(shapes, names, shape_count);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
