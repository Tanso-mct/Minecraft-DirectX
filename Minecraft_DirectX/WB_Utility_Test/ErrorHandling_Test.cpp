#include "pch.h"

#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

TEST(UtilityErrorHandling, MessageBox)
{
    WB::MessageBoxError("Test Error", "This is a test error message.");
}