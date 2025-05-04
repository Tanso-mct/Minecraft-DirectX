#pragma once

#include "WB_ConsoleLog/include/config.h"

#include "Interface/ConsoleLog.h"

#include <initializer_list>
#include <string>

namespace WB
{
    class CONSOLE_LOG_API ConsoleLog : public IConsoleLog
    {
    private:
        ConsoleLogConfig _config;

    public:
        ConsoleLog() = default;
        ~ConsoleLog() override = default;

        /***************************************************************************************************************
         * IConsoleLog interface implementation
        /**************************************************************************************************************/

        void Init(const ConsoleLogConfig& config) override;

        const std::string &GetName() const override;

        void Log(const std::initializer_list<const char*> &messages) const override;
        void LogWrn(const std::initializer_list<const char*> &messages) const override;

        std::string LogErr
        (
            const std::string& file, int line, const std::string& function,
            const std::initializer_list<const char*> &messages
        ) const override;
    };
}