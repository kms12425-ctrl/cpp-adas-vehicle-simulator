#include "ExecutorImpl.hpp"
#include <new>

namespace adas
{
    // 并没有初始化ExecutorImpl的pose成员变量
    ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : pose(pose) {}

    // Query方法
    Pose ExecutorImpl::Query(void) const noexcept
    {
        return pose;
    }

    // NewExecutor方法
    Executor *Executor::NewExecutor(const Pose &pose) noexcept
    {
        // return new (std::nothrow) ExecutorImpl(pose); // c++17
        // Cannot instantiate abstract ExecutorImpl; return nullptr until a concrete implementation is available.
        (void)pose;
        return nullptr;
    }
}