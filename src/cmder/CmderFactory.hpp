#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
    using Cmder = std::function<ActionGroup(PoseHandler &poseHandler, const CmderOrchestrator &orchestrator)>;
    using CmderList = std::list<Cmder>;
    class CmderFactory final
    {
    private:
        std::string ParseCommandString(std::string_view commands) const noexcept;
        void ReplaceAll(std::string &inout, std::string_view what, std::string with) const noexcept;

    private:
        const std::unordered_map<char, Cmder> cmderMap{
            // 前进
            {'M', MoveCommand()},
            // 后退
            {'B', ReverseCommand()},
            // 左转
            {'L', TurnLeftCommand()},
            // 右转
            {'R', TurnRightCommand()},
            // 加速
            {'F', FastCommand()},
            // 掉头
            {'Z', TurnRoundCommand()},
        };

    public:
        CmderFactory(void) = default;
        ~CmderFactory(void) = default;

        CmderFactory(const CmderFactory &) = delete;
        CmderFactory &operator=(const CmderFactory &) = delete;

    public:
        CmderList GetCmders(const std::string &commands) const noexcept;
    };
} // namespace adas
