#include <orb/flux.hpp>
#include <orb/print.hpp>

auto main() -> int
{
    for (auto i : flux::range(10))
    {
        orb::println("- {}", i);
    }

    return 0;
}
