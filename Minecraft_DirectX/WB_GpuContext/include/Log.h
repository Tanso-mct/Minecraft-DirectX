#pragma once

#include "Interface/ConsoleLog.h"

#include <memory>

namespace WBGpuContext
{
    std::unique_ptr<WB::IConsoleLog> &ConsoleLog();
} // namespace WBGpuContext