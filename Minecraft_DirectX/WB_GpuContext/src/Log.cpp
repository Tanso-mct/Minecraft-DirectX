#include "WB_GpuContext/include/Log.h"

#include "WB_ConsoleLog/include/ConsoleLog.h"
#pragma comment(lib, "WB_ConsoleLog.lib")

#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

std::unique_ptr<WB::IConsoleLog> &WBGpuContext::ConsoleLog()
{
    static std::unique_ptr<WB::IConsoleLog> consoleLog = std::make_unique<WB::ConsoleLog>
    (
        WB::ConsoleLogConfig
        (
            "WB_GpuContext",
            "\033[0m", // Normal color
            "\033[31m", // Red color
            "\033[33m"  // Yellow color
        )
    );
    
    return consoleLog;
}