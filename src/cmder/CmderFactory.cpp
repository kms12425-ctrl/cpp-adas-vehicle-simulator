#include "CmderFactory.hpp"

namespace adas
{
    std::list<Cmder> CmderFactory::GetCmders(const std::string &commands) const noexcept
    {
        std::list<Cmder> cmders;
        for (const auto cmd : ParseCommandString(commands))
        {
            // 根据操作查找表驱动
            const auto it = cmderMap.find(cmd);
            // 如果找到表驱动，执行操作指令
            if (it != cmderMap.end())
                cmders.push_back(it->second);
        }
        return cmders;
    }

    std::string CmderFactory::ParseCommandString(std::string_view commands) const noexcept
    {
        std::string result(commands);
        ReplaceAll(result, "TR", "Z");
        return result;
    }

    void CmderFactory::ReplaceAll(std::string &inout, std::string_view what, std::string with) const noexcept
    {
        for (
            std::string::size_type pos{};
            inout.npos != (pos = inout.find(what.data(), pos, what.length()));
            pos += with.length())
        {
            inout.replace(pos, what.length(), with.data(), with.length());
        }
    }

} // namespace adas
