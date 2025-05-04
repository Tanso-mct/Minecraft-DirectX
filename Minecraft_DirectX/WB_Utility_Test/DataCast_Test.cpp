#include "pch.h"

#include "WB_Utility/include/DataCast.h"
#pragma comment(lib, "WB_Utility.lib")

class IWeapon
{
public:
    virtual ~IWeapon() {}
};

class Sword : public IWeapon
{
public:
    int Use() const { return 1; }
};

TEST(UtilityDataCast, As)
{
    IWeapon* weapon = new Sword();

    {
        Sword* sword = WB::As<Sword>(weapon);
        EXPECT_EQ(sword->Use(), 1);
    }

    delete weapon; // Clean up the allocated memory
}

TEST(UtilityDataCast, UniqueAs)
{
    std::unique_ptr<IWeapon> weapon = std::make_unique<Sword>();

    {
        std::unique_ptr<Sword> sword = WB::UniqueAs<Sword>(weapon);
        EXPECT_EQ(sword->Use(), 1);
    }

    EXPECT_EQ(weapon, nullptr); // sword should be null after UniqueAs
}

TEST(UtilityDataCast, CastWithReturn)
{
    std::unique_ptr<IWeapon> weapon = std::make_unique<Sword>();

    {
        WB::CastWithReturn<Sword, IWeapon> sword(weapon);
        EXPECT_EQ(sword()->Use(), 1);

        EXPECT_EQ(weapon, nullptr); // weapon should be null after CastWithReturn
    }

    EXPECT_NE(weapon, nullptr); // weapon should be valid after CastWithReturn goes out of scope
}

