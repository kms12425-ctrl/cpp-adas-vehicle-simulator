#pragma once

#include "NormalOrchestrator.hpp"

namespace adas
{
    class BusOrchestrator : public NormalOrchestrator
    {
    public:
        ActionGroup TurnLeft(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);

            actionGroup.PushAction(GetStepAction(posehandler));
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION);
            return actionGroup;
        }

        ActionGroup TurnRight(const PoseHandler &posehandler) const noexcept override
        {
            ActionGroup actionGroup;
            actionGroup += OnFast(posehandler);

            actionGroup.PushAction(GetStepAction(posehandler));
            actionGroup.PushAction(posehandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION);
            return actionGroup;
        }
    };
}