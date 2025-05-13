#pragma once

#include "WB_ConsoleLog/include/Config.h"

#include "Interface/ConsoleLog.h"

#include <initializer_list>
#include <string>

namespace WB
{
    class CONSOLE_LOG_API ConsoleLog : public IConsoleLog
    {
    private:
        const ConsoleLogConfig _config;
        bool _isEnabled = true; // Default to enabled

    public:
        ConsoleLog(const ConsoleLogConfig& config);
        ~ConsoleLog() override = default;

        // Remove constructors with no arguments
        ConsoleLog() = delete;

        /***************************************************************************************************************
         * IConsoleLog interface implementation
        /**************************************************************************************************************/

        const std::string &GetName() const override;
        void SetIsEnabled(bool isEnabled) override;

        void Log(const std::initializer_list<const char*> &messages) const override;
        void LogWrn(const std::initializer_list<const char*> &messages) const override;

        std::string LogErr
        (
            const std::string& file, int line, const std::string& function,
            const std::initializer_list<const char*> &messages
        ) const override;
    };
}