#pragma once

#include <initializer_list>
#include <string>

namespace WB
{
    struct ConsoleLogConfig
    {
        std::string name = "ConsoleLog";

        std::string normalColor = "\033[0m"; // Normal color
        std::string errColor = "\033[31m"; // Red color
        std::string wrnColor = "\033[33m"; // Yellow color
    };

    class IConsoleLog
    {
    public:
        virtual ~IConsoleLog() = default;

        virtual void Init(const ConsoleLogConfig& config) = 0;

        virtual const std::string &GetName() const = 0;

        virtual void Log(const std::initializer_list<const char*> &messages) const = 0;
        virtual void LogWrn(const std::initializer_list<const char*> &messages) const = 0;

        virtual std::string LogErr
        (
            const std::string& file, int line, const std::string& function,
            const std::initializer_list<const char*> &messages
        ) const = 0;
    };

} // namespace WB