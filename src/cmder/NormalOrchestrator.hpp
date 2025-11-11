#pragma once
#include "CmderOrchestrator.hpp"

namespace adas
{
    class NormalOrchestrator : public CmderOrchestrator
    {
    public:
        ActionGroup Move(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(GetStepAction(posehandler));
            return actionGroup;
        }
        ActionGroup TurnLeft(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION);
            return actionGroup;
        }
        ActionGroup TurnRight(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION);
            return actionGroup;
        }
        ActionGroup TurnRound(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            if (posehandler.IsReverse())
                return actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            return actionGroup;
        }

    protected:
        // 每次移动都需要判断是否处于倒车状态，因此将其作为一个方法独立出来
        ActionType GetStepAction(const PoseHandler &posehandler) const noexcept
        {
            return posehandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION : ActionType::FORWARD_1_STEP_ACTION;
        }

        // 如果处于加速状态，先移动一步；如果处于未加速状态，则返回空数组
        ActionGroup OnFast(const PoseHandler &posehandler) const noexcept
        {
            if (posehandler.IsFast())
                return ActionGroup({GetStepAction(posehandler)});
            return ActionGroup();
        }
    }; // namespace adas
}