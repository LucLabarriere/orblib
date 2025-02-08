#include <orb/files.hpp>
#include <orb/print.hpp>

auto main(int, char** argv) -> int
{
    orb::path p1("inexistant.txt");
    orb::println("'{}' is readable ? -> {}", p1.c_str(), p1.readable());
    orb::println("'{}' is executable ? -> {}", p1.data(), p1.executable());
    orb::println("'{}' exists ? -> {}", p1.data(), p1.exists());
    orb::println("'{}' has filename: '{}'", p1.data(), p1.filename());
    orb::println("'{}' has extension: '{}'", p1.data(), p1.extension());

    orb::path p2(argv[0]);
    orb::println("'{}' is readable ? -> {}", p2.data(), p2.readable());
    orb::println("'{}' is executable ? -> {}", p2.data(), p2.executable());
    orb::println("'{}' exists ? -> {}", p2.data(), p2.exists());
    orb::println("'{}' is directory ? -> {}", p2.data(), p2.is_dir());

    orb::println("'{}' has filename: '{}'", p2.data(), p2.filename());
    orb::println("'{}' has extension: '{}'", p2.data(), p2.extension());

    const orb::path parent = std::string { p2.parent() };

    auto res = orb::path::ls(parent.c_str());

    orb::println("");
    orb::println("Listing files in directory {}", parent.c_str());

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
