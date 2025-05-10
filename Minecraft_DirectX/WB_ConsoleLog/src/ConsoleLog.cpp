#include "WB_ConsoleLog/include/ConsoleLog.h"

#include <windows.h>
#include <iostream>

WB::ConsoleLog::ConsoleLog(const ConsoleLogConfig &config)
: _config(config)
{

}

const std::string &WB::ConsoleLog::GetName() const
{
    return _config.name;
}

void WB::ConsoleLog::SetIsEnabled(bool isEnabled)
{
    _isEnabled = isEnabled;
}

void WB::ConsoleLog::Log(const std::initializer_list<const char*> &messages) const
{
    if (!_isEnabled) return; // If logging is disabled, do nothing

    std::cout << _config.normalColor;
    for (const auto &message : messages)
    {
        // Log to Windows Console
        std::cout << message << std::endl;

        // Log to Visual Studio Debug Console
        OutputDebugStringA(message);
        OutputDebugStringA("\n");
    }
}

void WB::ConsoleLog::LogWrn(const std::initializer_list<const char*> &messages) const
{
    if (!_isEnabled) return; // If logging is disabled, do nothing

    std::cout << _config.wrnColor;
    for (const auto &message : messages)
    {
        // Log to Windows Console
        std::cout << message << std::endl;

        // Log to Visual Studio Debug Console
        OutputDebugStringA(message);
        OutputDebugStringA("\n");
    }
    std::cout << _config.normalColor;
}

std::string WB::ConsoleLog::LogErr
(
    const std::string& file, int line, const std::string& function,
    const std::initializer_list<const char*> &messages
) const 
{
    std::string errMsg = "";
    for (const auto &message : messages)
    {
        // Append message to error message
        errMsg += message + std::string("\n");
    }

    errMsg += file + " : " + std::to_string(line) + "\n";
    errMsg += function + "\n";

    // Log to Windows Console
    std::cout << _config.errColor;
    std::cout << errMsg;
    std::cout << _config.normalColor;

    // Log to Visual Studio Debug Console
    OutputDebugStringA(errMsg.c_str());

    return errMsg;
}