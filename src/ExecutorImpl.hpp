#pragma once

#include "Executor.hpp"
#include <string>

namespace adas
{
    /*
        Executor的具体实现
    */
    class ExecutorImpl final : public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose) noexcept;
        // 默认析构函数
        ~ExecutorImpl() noexcept = default;
        // 不能拷贝
        ExecutorImpl(const ExecutorImpl &) = delete;
        // 不能赋值
        ExecutorImpl &operator=(const ExecutorImpl &) = delete;

    public:
        // 查询当前汽车姿态,是父类抽象方法Query的具体实现
        Pose Query(void) const noexcept override;
        // 通过命令执行驾驶动作，纯虚函数，留给子类具体实现
        void Execute(const std::string &commands) noexcept override;

    private:
        // 当前汽车姿态
        Pose pose;
        bool isFast;
        void Move(void) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;

    private:
        class ICommand
        {
        public:
            // 在这里给出析构函数和纯虚函数 DoOperate的声明
            virtual ~ICommand() = default;
            virtual void DoOperate(ExecutorImpl &ExecutorImpl) const noexcept = 0;
        };

    private:
        class MoveCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override
            {
                executor.Move();
            }
        };
        class TurnLeftCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override
            {
                executor.TurnLeft();
            }
        };
        class TurnRightCommand final : public ICommand
        {
        public:
            void DoOperate(ExecutorImpl &executor) const noexcept override
            {
                executor.TurnRight();
            }
        };
    };
}