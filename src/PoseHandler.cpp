#include "PoseHandler.hpp"

namespace adas
{
    PoseHandler::PoseHandler(const Pose &pose) noexcept : point(pose.x, pose.y), facing(&Direction::GetDirection(pose.heading)) {}
    void PoseHandler::Forward() noexcept // Forward 方法
    {
        // 将当前坐标加上方向向量
        point += facing->Move();
    }
    void PoseHandler::Backward() noexcept // Backward 方法
    {
        point -= facing->Move();
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
    void PoseHandler::Reverse() noexcept
    {
        isReverse = !isReverse;
    }

    bool PoseHandler::IsFast(void) const noexcept
    {
        return isFast;
    }
    bool PoseHandler::IsReverse(void) const noexcept
    {
        return isReverse;
    }

    // Query方法
    Pose PoseHandler::Query(void) const noexcept
    {
        return {point.GetX(), point.GetY(), facing->GetHeading()};
    }
} // namespace adas
