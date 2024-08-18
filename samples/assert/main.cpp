#include <orb/assert.hpp>

auto main() -> int
{
    int myvar = 5;
    orbassert(myvar == 5, "Failure: This should not be executed since value is {}=={}", myvar, 5);
    orbassert(myvar == 6, "Success: This is executed since value is {}!={}", myvar, 6);

#ifndef ORB_ASSERT
    orb::print("Sample cannot be ran since asserts are disabled");
#endif
    return 0;
}
