#pragma once

#include "Executor.hpp"
#include "cmder/CmderOrchestrator.hpp"
#include "core/PoseHandler.hpp"

#include <string>
#include <memory>

namespace adas
{
    /*
        Executor的具体实现
    */
    class ExecutorImpl final : public Executor
    {
    public:
        // 构造函数
        explicit ExecutorImpl(const Pose &pose, CmderOrchestrator *orchestrator) noexcept;
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
        PoseHandler poseHandler; // 状态管理类
        std::unique_ptr<CmderOrchestrator> orchestrator;
    };
}