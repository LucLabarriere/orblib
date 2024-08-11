#include <orb/files.hpp>
#include <orb/print.hpp>

auto main(int, char** argv) -> int
{
    orb::path p1("inexistant.txt");
    orb::println("'{}' is readable ? -> {}", p1.data(), p1.readable());
    orb::println("'{}' is writable ? -> {}", p1.data(), p1.writable());
    orb::println("'{}' is executable ? -> {}", p1.data(), p1.executable());
    orb::println("'{}' exists ? -> {}", p1.data(), p1.exists());

    orb::path p2(argv[0]);
    orb::println("'{}' is readable ? -> {}", p2.data(), p2.readable());
    orb::println("'{}' is writable ? -> {}", p2.data(), p2.writable());
    orb::println("'{}' is executable ? -> {}", p2.data(), p2.executable());
    orb::println("'{}' exists ? -> {}", p2.data(), p2.exists());
    orb::println("'{}' is directory ? -> {}", p2.data(), p2.is_dir());

    auto res = orb::path::ls(argv[0]);
    if (res.is_error())
    {
        orb::println("{}", res.error().get_message());
    }

    else
    {
        for (const auto& f : res.value())
        {
            orb::println(" - {}", f.data());
        }
    }
    return 0;
}