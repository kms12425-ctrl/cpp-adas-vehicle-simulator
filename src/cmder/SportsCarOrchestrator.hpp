#pragma once

#include "NormalOrchestrator.hpp"

namespace adas
{
    class SportsCarOrchestrator : public NormalOrchestrator
    {
    public:
        ActionGroup Move(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(GetStepAction(posehandler));
            actionGroup.PushAction(GetStepAction(posehandler));
            // if (posehandler.IsFast())
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            // else
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            return actionGroup;
        }
        ActionGroup TurnLeft(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION);
            actionGroup.PushAction(GetStepAction(posehandler));

            // if (posehandler.IsFast())
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            // else
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            return actionGroup;
        }
        ActionGroup TurnRight(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION);
            actionGroup.PushAction(GetStepAction(posehandler));

            // if (posehandler.IsFast())
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //         actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            // else
            // {
            //     if (posehandler.IsReverse())
            //     {
            //         actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
            //         actionGroup.PushAction(ActionType::BACKWARD_1_STEP_ACTION);
            //     }
            //     else
            //     {
            //         actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
            //         actionGroup.PushAction(ActionType::FORWARD_1_STEP_ACTION);
            //     }
            // }
            return actionGroup;
        }
    };
}