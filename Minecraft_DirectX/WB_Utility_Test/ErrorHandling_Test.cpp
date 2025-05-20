#include "pch.h"

#include "WB_Utility/include/ErrorHandling.h"
#pragma comment(lib, "WB_Utility.lib")

TEST(UtilityErrorHandling, MessageBoxTest)
{
     WB::MessageBoxError("Test Error", "This is a test error message.");
}

TEST(UtilityErrorHandling, HrToString)
{
    HRESULT hr = E_FAIL;
    std::string errorMessage = WB::HrToString(hr);
    // WB::MessageBoxError("Test Error", errorMessage);

    EXPECT_FALSE(errorMessage.empty());
}