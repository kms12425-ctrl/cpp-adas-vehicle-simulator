#pragma once
#include "Executor.hpp"
#include "Direction.hpp"

namespace adas
{
    class PoseHandler final
    {
    private:
        Point point;
        const Direction *facing; // 当前汽车姿态
        bool isFast{false};      // 是否为Fast状态
    public:
        void Move(void) noexcept;         // 移动方法
        void TurnLeft(void) noexcept;     // 左转方法
        void TurnRight(void) noexcept;    // 右转方法
        void Fast(void) noexcept;         // 改变Fast状态
        bool IsFast(void) const noexcept; // 查询是否为Fast状态
        Pose Query(void) const noexcept;

    public:
        PoseHandler(const Pose &pose) noexcept;
        PoseHandler(const PoseHandler &) = delete;            // 禁止拷贝构造
        PoseHandler &operator=(const PoseHandler &) = delete; // 禁止拷贝赋值
    };
} // namespace
