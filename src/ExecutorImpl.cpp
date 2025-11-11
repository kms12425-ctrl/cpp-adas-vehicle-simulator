// #include "Command.hpp"
#include "ExecutorImpl.hpp"
#include "core/Singleton.hpp"
#include "cmder/CmderFactory.hpp"
#include "cmder/BusOrchestrator.hpp"
#include "cmder/NormalOrchestrator.hpp"
#include "cmder/SportsCarOrchestrator.hpp"

#include <algorithm>
// #include <unordered_map>
// #include <memory>
// #include <new>

namespace adas
{
    // 并没有初始化ExecutorImpl的pose成员变量
    ExecutorImpl::ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept : poseHandler(pose), orchestrator(orchestrator) {}

    Pose ExecutorImpl::Query() const noexcept
    {
        return poseHandler.Query();
    }

    // NewExecutor方法
    // Executor *Executor::NewExecutor(const Pose &pose) noexcept
    // {
    //     return new (std::nothrow) ExecutorImpl(pose); // c++17
    // }
    Executor *Executor::NewExecutor(const Pose &pose,
                                    const ExecutorType executorType) noexcept
    {
        CmderOrchestrator *orchestrator = nullptr;
        switch (executorType)
        {
        case ExecutorType::BUS:
            orchestrator = new (std::nothrow) BusOrchestrator();
            /* code */
            break;
        case ExecutorType::SPORTS_CAR:
            orchestrator = new (std::nothrow) SportsCarOrchestrator();
            /* code */
            break;
        case ExecutorType::NORMAL:
            orchestrator = new (std::nothrow) NormalOrchestrator();
            /* code */
            break;
        }
        return new (std::nothrow) ExecutorImpl(pose, orchestrator); // c++17
    }

    void ExecutorImpl::Execute(const std::string &commands) noexcept
    {
        const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

        std::for_each(
            cmders.begin(),
            cmders.end(),
            [this](const Cmder &cmder) noexcept
            {
                cmder(poseHandler, *orchestrator).DoOperate(poseHandler);
            });
        // std::unordered_map<char, std::function<void(PoseHandler & PoseHandler)>> cmderMap{
        //     // 前进
        //     {'M', MoveCommand()},
        //     // 后退
        //     {'B', ReverseCommand()},
        //     // 左转
        //     {'L', TurnLeftCommand()},
        //     // 右转
        //     {'R', TurnRightCommand()},
        //     // 加速
        //     {'F', FastCommand()},

        // };

        // // 前进
        // cmderMap.emplace('M', MoveCommand());

        // // 左转
        // cmderMap.emplace('L', TurnLeftCommand());

        // // 右转
        // cmderMap.emplace('R', TurnRightCommand());

        // // 加速
        // cmderMap.emplace('F', FastCommand());

        // for (const auto cmd : command)
        // {
        //     // 根据操作查找表驱动
        //     const auto it = cmderMap.find(cmd);
        //     // 如果找到表驱动，执行操作指令
        //     if (it != cmderMap.end())
        //         it->second(poseHandler);
        // std::unique_ptr<ICommand> cmder = nullptr;
        // if (cmd == 'M')
        // {
        //     // 智能指针指向 MoveCommand实例
        //     cmder = std::make_unique<MoveCommand>();
        // }

        // else if (cmd == 'L')
        // {
        //     // 智能指针指向 TurnLeftCommand实例
        //     cmder = std::make_unique<TurnLeftCommand>();
        // }

        // else if (cmd == 'R')
        // {
        //     // 智能指针指向 TurnRightCommand实例
        //     cmder = std::make_unique<TurnRightCommand>();
        // }

        // else if (cmd == 'F')
        // {
        //     cmder = std::make_unique<FastCommand>();
        // }

        // else if (cmd == 'B')
        // {
        //     cmder = std::make_unique<ReverseCommand>()
        // }
        // if (cmder)
        //     cmder->DoOperate(poseHandler);
    }
}