
#include "CmderFactory.hpp"

namespace adas
{
    std::list<std::function<void(PoseHandler &poseHandler)>> CmderFactory::GetCmders(const std::string &commands) const noexcept
    {
        std::list<std::function<void(PoseHandler & PoseHandler)>> cmders;
        for (const auto cmd : commands)
        {
            // 根据操作查找表驱动
            const auto it = cmderMap.find(cmd);
            // 如果找到表驱动，执行操作指令
            if (it != cmderMap.end())
                cmders.push_back(it->second);
        }
        return cmders;
    }
} // namespace adas
