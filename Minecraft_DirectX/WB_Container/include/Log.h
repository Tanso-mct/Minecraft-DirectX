#pragma once

#include "WB_Container/include/Config.h"

#include "WB_ConsoleLog/include/ConsoleLog.h"
#pragma comment(lib, "WB_ConsoleLog.lib")

#include <memory>

namespace WBContainer
{
    CONTAINER_API std::unique_ptr<WB::IConsoleLog>& ConsoleLog();
}