#include <orb/assert.hpp>
#include <orb/dynlib.hpp>
#include <orb/files.hpp>
#include <orb/platform.hpp>
#include <orb/print.hpp>

#include "testlib.hpp"

auto main(int, char** arv) -> int
{
    orb::path workdir { arv[0] };
    workdir            = workdir.parent();
    orb::path lib_path = orb::dynlib::get_libfile_path(workdir.slash("sample_dynlib_testlib"));

    orb::println("- Workdir: {}", workdir.parent());
    orb::println("- libfile: {}", lib_path.view());

    orb::dynlib library;

    library.open(lib_path);
    if (!library.is_valid())
    {
        orb::println("Error occured: {}", library.get_err());
        orb::panic("Could not load dynamic library {}", lib_path.data());
    }

    auto func = library.get_func<decltype(&orb::orb_testlibfunc)>("orb_testlibfunc");

    if (!func)
    {
        orb::println("Error occured: {}", library.get_err());
        orb::panic("Could not load function");
    }

    orb::println("- Executing 'void testlibfunc()'");
    func();

    return 0;
}
