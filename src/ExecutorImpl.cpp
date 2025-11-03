#include "Command.hpp"
#include "ExecutorImpl.hpp"

#include <unordered_map>
#include <memory>
#include <new>

namespace adas
{
    // 并没有初始化ExecutorImpl的pose成员变量
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose) {}

    Pose ExecutorImpl::Query() const noexcept
    {
        return poseHandler.Query();
    }

    // NewExecutor方法
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        return new (std::nothrow) ExecutorImpl(pose); // c++17
    }

    void ExecutorImpl::Execute(const std::string &command) noexcept
    {
        std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;
        cmderMap.emplace('M', std::make_unique<MoveCommand>());
        cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
        cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
        cmderMap.emplace('F', std::make_unique<FastCommand>());

        for (const auto cmd : command)
        {
            // 根据操作查找表驱动
            const auto it = cmderMap.find(cmd);
            // 如果找到表驱动，执行操作指令
            if (it != cmderMap.end())
                it->second->DoOperate(poseHandler);
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

}