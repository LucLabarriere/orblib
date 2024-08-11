#include <orb/assert.hpp>
#include <orb/dynlib.hpp>
#include <orb/files.hpp>
#include <orb/print.hpp>

#include "testlib.hpp"

auto main(int, char** arv) -> int
{
    orb::path compiler_path { ORB_COMPILER };
    orb::path workdir { arv[0] };
    workdir = workdir.parent();

    orb::println("- Compiler path: {}", compiler_path.data());
    orb::println("- Compiler is {}", compiler_path.filename());

    orb::println("- Workdir: {}", workdir.parent());
    auto files = workdir.ls().value();
    for (const auto& file : files)
    {
        if (file.basename() == "libsample_compiler_testlib")
        {
            orb::path absolute_path(workdir + "/" + file);
            orb::println("- Found test library file: {}", absolute_path.data());
            orb::dynlib library;

            library.open(absolute_path.data());
            if (!library.is_valid())
            {
                orb::println("Error occured: {}", library.get_err());
                orb::panic("Could not load dynamic library {}", absolute_path.data());
            }

            auto* f = library.get_func(orb::orb_testlibfunc, "orb_testlibfunc");

            if (!f)
            {
                orb::println("Error occured: {}", library.get_err());
                orb::panic("Could not load function");
            }

            orb::println("- Executing 'void testlibfunc()'");
            f();

            library.close();
            break;
        }
    }

    return 0;
}
