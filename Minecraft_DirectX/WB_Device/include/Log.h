#pragma once

#include "Interface/ConsoleLog.h"

#include <memory>

namespace WBDevice
{
    std::unique_ptr<WB::IConsoleLog> &ConsoleLog();
} // namespace WBWindowContext