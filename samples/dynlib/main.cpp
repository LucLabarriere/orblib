#include <orb/assert.hpp>
#include <orb/dynlib.hpp>
#include <orb/files.hpp>
#include <orb/print.hpp>

#include "testlib.hpp"

auto main(int, char** arv) -> int
{
    orb::path workdir { arv[0] };
    workdir            = workdir.parent();
    orb::path lib_path = workdir + "/libsample_dynlib_testlib.dylib";

    orb::println("- Workdir: {}", workdir.parent());
    orb::println("- libfile: {}", lib_path.data());

    orb::dynlib library;

    library.open(lib_path.data());
    if (!library.is_valid())
    {
        orb::println("Error occured: {}", library.get_err());
        orb::panic("Could not load dynamic library {}", lib_path.data());
    }

    auto* f = library.get_func(orb::orb_testlibfunc, "orb_testlibfunc");

    if (!f)
    {
        orb::println("Error occured: {}", library.get_err());
        orb::panic("Could not load function");
    }

    orb::println("- Executing 'void testlibfunc()'");
    f();

    return 0;
}
