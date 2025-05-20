#pragma once

#include "Interface/ConsoleLog.h"

#include <memory>

namespace WBRender
{
    std::unique_ptr<WB::IConsoleLog> &ConsoleLog();
} // namespace WBWindowContext