#include "PoseHandler.hpp"

namespace adas
{
    PoseHandler::PoseHandler(const Pose &pose) noexcept : point(pose.x, pose.y), facing(&Direction::GetDirection(pose.heading)) {}
    void PoseHandler::Move() noexcept // Move 方法
    {
        // 将当前坐标加上方向向量
        point += facing->Move();
    }
    void PoseHandler::TurnLeft() noexcept // Turn Left 方法
    {
        facing = &(facing->LeftOne());
    }
    void PoseHandler::TurnRight() noexcept // Turn Right方法
    {
        facing = &(facing->RightOne());
    }
    void PoseHandler::Fast() noexcept
    {
        isFast = !isFast;
    }
    bool PoseHandler::IsFast(void) const noexcept
    {
        return isFast;
    }
    // Query方法
    Pose PoseHandler::Query(void) const noexcept
    {
        return {point.GetX(), point.GetY(), facing->GetHeading()};
    }
} // namespace adas
