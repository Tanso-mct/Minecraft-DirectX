#include "pch.h"

#include "WB_ConsoleLog/include/ConsoleLog.h"
#pragma comment(lib, "WB_ConsoleLog.lib")

TEST(ConsoleLog, Create)
{
    WB::ConsoleLogConfig config;
    config.name = "Test"; // Name of the console log
    config.normalColor = "\033[0m"; // Normal color
    config.errColor = "\033[31m"; // Red color
    config.wrnColor = "\033[33m"; // Yellow color

    WB::ConsoleLog consoleLog;
    consoleLog.Init(config);
}

TEST(ConsoleLog, Log)
{
    WB::ConsoleLogConfig config;
    config.name = "Test"; // Name of the console log
    config.normalColor = "\033[0m"; // Normal color
    config.errColor = "\033[31m"; // Red color
    config.wrnColor = "\033[33m"; // Yellow color

    WB::ConsoleLog consoleLog;
    consoleLog.Init(config);

    consoleLog.Log({"Hello", "World"});
    consoleLog.LogWrn({"Warning", "Message"});

    std::string errMsg = consoleLog.LogErr
    (
        __FILE__, __LINE__, __FUNCTION__, 
        {"Error", "Message"}
    );

    MessageBoxA
    (
        nullptr,
        errMsg.c_str(),
        (consoleLog.GetName() + "Error").c_str(),
        MB_OK | MB_ICONERROR | MB_TASKMODAL | MB_SETFOREGROUND | MB_TOPMOST
    );

    // throw std::runtime_error(errMsg); // This will cause the test to fail
}