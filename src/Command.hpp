#pragma once
#include "PoseHandler.hpp"
#include "ActionGroup.hpp"

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
        // const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.Move();
        // };

        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //             poseHandler.Backward();
        //         else
        //             poseHandler.Forward();
        //     }
        //     if (poseHandler.IsReverse())
        //         poseHandler.Backward();
        //     else
        //         poseHandler.Forward();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            // 创建ActionGroup对象
            ActionGroup actionGroup;

            // 如果当前是倒车状态，action为ActionType::BACKWARD_1_STEP_ACTION
            // 如果当前不是倒车状态，action为ActionType::FORWARD_1_STEP_ACTION
            const auto action = poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;

            // 如果当前是加速状态，则额外执行一次action
            /// 所以要额外地将action加到ActionGroup
            // 因为ActionGroup里面是执行的action的序列
            if (poseHandler.IsFast())
                actionGroup.PushAction(action);
            actionGroup.PushAction(action);
            return actionGroup;
        }
    };

    class ReverseCommand final
    {
    public:
        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     poseHandler.Reverse();
        // }

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            // 创建ActionGroup对象
            ActionGroup actionGroup;
            const auto action = ActionType::BE_REVERSE_ACTION;
            actionGroup.PushAction(action);
            return actionGroup;
        }
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
        // const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.TurnLeft();
        // };

        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //             poseHandler.Backward();
        //         else
        //             poseHandler.Forward();
        //     }
        //     if (poseHandler.IsReverse())
        //         poseHandler.TurnRight();
        //     else
        //         poseHandler.TurnLeft();
        // };

        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            // 创建ActionGroup对象
            ActionGroup actionGroup;
            if (poseHandler.IsFast())
            {
                if (poseHandler.IsReverse())
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                else
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            }
            if (poseHandler.IsReverse())
                actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            else
                actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            return actionGroup;
        }
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
        // const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     if (poseHandler.IsFast())
        //         poseHandler.Move();
        //     poseHandler.TurnRight();
        // };
        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     if (poseHandler.IsFast())
        //     {
        //         if (poseHandler.IsReverse())
        //             poseHandler.Backward();
        //         else
        //             poseHandler.Forward();
        //     }
        //     if (poseHandler.IsReverse())
        //         poseHandler.TurnLeft();
        //     else
        //         poseHandler.TurnRight();
        // };
        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            // 创建ActionGroup对象
            ActionGroup actionGroup;
            if (poseHandler.IsFast())
            {
                if (poseHandler.IsReverse())
                    actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
                else
                    actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            }
            if (poseHandler.IsReverse())
                actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            else
                actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            return actionGroup;
        }
    };

    class FastCommand final //: public ICommand
    {
    public:
        // void DoOperate(PoseHandler &poseHandler) const noexcept override
        // {
        //     poseHandler.Fast();
        // }
        // const std::function<void(PoseHandler &PoseHandler)> operate = [](PoseHandler &poseHandler) noexcept
        // {
        //     poseHandler.Fast();
        // };
        // void operator()(PoseHandler &poseHandler) const noexcept
        // {
        //     poseHandler.Fast();
        // }
        ActionGroup operator()(PoseHandler &poseHandler) const noexcept
        {
            // 创建ActionGroup对象
            ActionGroup actionGroup;
            const auto action = ActionType::BE_FAST_ACTION;
            actionGroup.PushAction(action);
            return actionGroup;
        }
    };
}