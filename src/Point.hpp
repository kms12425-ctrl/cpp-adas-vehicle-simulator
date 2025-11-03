#pragma once

namespace adas
{
    class Point final
    {
    private:
        int x; // x坐标
        int y; // y坐标

    public:
        int GetX(void) const noexcept;
        int GetY(void) const noexcept;

    public:
        Point(const int x, const int y) noexcept;
        Point(const Point &rhs) noexcept; // 拷贝构造

        Point &operator=(const Point &rhs) noexcept;  // 拷贝赋值
        Point &operator+=(const Point &rhs) noexcept; // 移动
    };
} // namespace adas
