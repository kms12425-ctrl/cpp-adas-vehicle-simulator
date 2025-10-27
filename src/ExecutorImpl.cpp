#include "ExecutorImpl.hpp"
#include <memory>
#include <new>

namespace adas
{
    // 并没有初始化ExecutorImpl的pose成员变量
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose), isFast(false) {}

    // Query方法
    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    // NewExecutor方法
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose); // c++17
    }
    void ExecutorImpl::Execute(const std::string &command) noexcept
    {
        for (const auto cmd : command)
        {

            if (cmd == 'M')
            {
                // 智能指针指向 MoveCommand实例，不用担心delete了
                std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
                //*this就是 ExecutorImpl实例对象，作为实参 传递给 DoOperate方法
                cmder->DoOperate(*this);
            }
            if (cmd == 'L')
            {
                // 智能指针指向 TurnLeftCommand实例，不用担心delete了
                std::unique_ptr<TurnLeftCommand> cmder = std::make_unique<TurnLeftCommand>();
                //*this就是 ExecutorImpl实例对象，作为实参 传递给 DoOperate方法
                cmder->DoOperate(*this);
            }
            else if (cmd == 'R')
            {
                // 智能指针指向 TurnRightCommand实例，不用担心delete了
                std::unique_ptr<TurnRightCommand> cmder = std::make_unique<TurnRightCommand>();
                //*this就是 ExecutorImpl实例对象，作为实参 传递给 DoOperate方法
                cmder->DoOperate(*this);
            }
            else if (cmd == 'F')
                isFast = !isFast;
        }
    }
    void ExecutorImpl::Move() noexcept // Move 方法
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
    void ExecutorImpl::TurnLeft() noexcept // Turn Left 方法
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
    void ExecutorImpl::TurnRight() noexcept // Turn Right方法
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

}