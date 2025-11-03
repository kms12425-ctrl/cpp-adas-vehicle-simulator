#include "PoseHandler.hpp"

namespace adas
{
    PoseHandler::PoseHandler(const Pose &pose) noexcept : pose(pose), isFast() {}
    void PoseHandler::Move() noexcept // Move 方法
    {
        if (pose.heading == 'E')
            pose.x++;
        else if (pose.heading == 'S')
            pose.y--;
        else if (pose.heading == 'W')
            pose.x--;
        else if (pose.heading == 'N')
            pose.y++;
    }
    void PoseHandler::TurnLeft() noexcept // Turn Left 方法
    {
        if (pose.heading == 'E')
            pose.heading = 'N';
        else if (pose.heading == 'S')
            pose.heading = 'E';
        else if (pose.heading == 'W')
            pose.heading = 'S';
        else if (pose.heading == 'N')
            pose.heading = 'W';
    }
    void PoseHandler::TurnRight() noexcept // Turn Right方法
    {
        if (pose.heading == 'E')
            pose.heading = 'S';
        else if (pose.heading == 'W')
            pose.heading = 'N';
        else if (pose.heading == 'N')
            pose.heading = 'E';
        else if (pose.heading == 'S')
            pose.heading = 'W';
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
        return pose;
    }
} // namespace adas
