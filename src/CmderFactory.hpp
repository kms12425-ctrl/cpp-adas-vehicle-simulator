#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
    using Cmder = std::function<void(PoseHandler &poseHandler)>;
    using CmderList = std::list<Cmder>;
    class CmderFactory final
    {
    private:
        const std::unordered_map<char, std::function<void(PoseHandler &poseHandler)>> cmderMap{
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
        };

    public:
        CmderFactory(void) = default;
        ~CmderFactory(void) = default;

        CmderFactory(const CmderFactory &) = delete;
        CmderFactory &operator=(const CmderFactory &) = delete;

    public:
        std::list<std::function<void(PoseHandler &poseHandler)>> GetCmders(const std::string &commands) const noexcept;
    };
} // namespace adas
