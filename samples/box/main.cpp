#include <orb/box.hpp>
#include <orb/print.hpp>

auto main() -> int {
    orb::box<int> ptr = orb::make_box<int>(5);
    orb::weak<int> wmut = ptr.getmut();
    *wmut = 8;
    orb::weak<const int> wconst = ptr.get();

    return 0;
}
