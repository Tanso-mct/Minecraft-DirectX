#include "WB_Container/include/Log.h"

std::unique_ptr<WB::IConsoleLog> &WBContainer::ConsoleLog()
{
    static std::unique_ptr<WB::IConsoleLog> consoleLog = std::make_unique<WB::ConsoleLog>
    (
        WB::ConsoleLogConfig
        (
            "WB_Container",
            "\033[0m", // Normal color
            "\033[31m", // Red color
            "\033[33m"  // Yellow color
        )
    );
    
    return consoleLog;
}