#include "Point.hpp"

namespace adas
{
    int Point::GetX() const noexcept
    {
        return this->x;
    }

    int Point::GetY() const noexcept
    {
        return this->y;
    }

    Point::Point(const int x, const int y) noexcept : x(x), y(y) {}

    Point::Point(const Point &rhs) noexcept : x(rhs.x), y(rhs.y) {}

    Point &Point::operator=(const Point &rhs) noexcept
    {
        if (this != &rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
        }
        return *this;
    }

    Point &Point::operator+=(const Point &rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
} // namespace adas
