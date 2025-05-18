#pragma once

#include "Interface/ConsoleLog.h"

#include <memory>

namespace WBWindowContext
{
    std::unique_ptr<WB::IConsoleLog> &ConsoleLog();
} // namespace WBWindowContext