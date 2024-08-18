#pragma once

#include <orb/platform.hpp>

#ifdef ORB_WINDOWS
#define TEST_LIB_EXPORT __declspec(dllexport) extern "C"
#else
#define TEST_LIB_EXPORT extern "C"
#endif

namespace orb
{
    TEST_LIB_EXPORT void orb_testlibfunc();
}
