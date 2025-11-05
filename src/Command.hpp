#pragma once
#include "PoseHandler.hpp"

#include <functional>

namespace adas
{
    // class ICommand
    // {
    // public:
    //     // 在这里给出析构函数和纯虚函数 DoOperate的声明
    //     virtual ~ICommand() = default;
    //     virtual void DoOperate(PoseHandler &poseHandler) const noexcept = 0;
    // };

    class MoveCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.Move();
        // }

        // 定义函数对象operator，接收函数PoseHandler，返回void
        const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        {
            if (poseHandler.IsFast())
                poseHandler.Move();
            poseHandler.Move();
        };
    };

    class TurnLeftCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.TurnLeft();
        // }
        // 定义函数对象operator，接收函数PoseHandler，返回void
        const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        {
            if (poseHandler.IsFast())
                poseHandler.Move();
            poseHandler.TurnLeft();
        };
    };

    class TurnRightCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.TurnRight();
        // }
        // 定义函数对象operator，接收函数PoseHandler，返回void
        const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        {
            if (poseHandler.IsFast())
                poseHandler.Move();
            poseHandler.TurnRight();
        };
    };

    class FastCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     poseHandler.Fast();
        // }
        const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        {
            poseHandler.Fast();
        };
    };
}
