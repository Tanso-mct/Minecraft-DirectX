#include "WB_ConsoleLog/include/ConsoleLog.h"

#include <iostream>

void WB::ConsoleLog::Init(const ConsoleLogConfig &config)
{
    _config = config;
}

const std::string &WB::ConsoleLog::GetName() const
{
    return _config.name;
}

void WB::ConsoleLog::Log(const std::initializer_list<const char*> &messages) const
{
    std::cout << _config.normalColor;
    for (const auto &message : messages)
    {
        std::cout << message << std::endl;
    }
}

void WB::ConsoleLog::LogWrn(const std::initializer_list<const char*> &messages) const
{
    std::cout << _config.wrnColor;
    for (const auto &message : messages)
    {
        std::cout << message << std::endl;
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

    std::cout << _config.errColor;
    for (const auto &message : messages)
    {
        std::cout << message << std::endl;
        errMsg += message + std::string("\n");
    }
    std::cout << _config.normalColor;

    errMsg += "\n";
    errMsg += file + " : " + std::to_string(line) + "\n";
    errMsg += function + "\n";

    return errMsg;
}