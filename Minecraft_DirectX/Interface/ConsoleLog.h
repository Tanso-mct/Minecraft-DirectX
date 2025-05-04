#pragma once

#include <initializer_list>
#include <string>

namespace WB
{
    struct ConsoleLogConfig
    {
        ConsoleLogConfig
        (
            const std::string& name = "ConsoleLog",
            const std::string& normalColor = "\033[0m",
            const std::string& errColor = "\033[31m",
            const std::string& wrnColor = "\033[33m"
        ){
            this->name = name;
            this->normalColor = normalColor;
            this->errColor = errColor;
            this->wrnColor = wrnColor;
        }

        std::string name = "ConsoleLog";

        std::string normalColor = "\033[0m"; // Normal color
        std::string errColor = "\033[31m"; // Red color
        std::string wrnColor = "\033[33m"; // Yellow color
    };

    class IConsoleLog
    {
    public:
        virtual ~IConsoleLog() = default;

        virtual const std::string &GetName() const = 0;
        virtual void SetIsEnabled(bool isEnabled) = 0;

        virtual void Log(const std::initializer_list<const char*> &messages) const = 0;
        virtual void LogWrn(const std::initializer_list<const char*> &messages) const = 0;

        virtual std::string LogErr
        (
            const std::string& file, int line, const std::string& function,
            const std::initializer_list<const char*> &messages
        ) const = 0;
    };

} // namespace WB