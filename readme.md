# OrbLib
C++ 23 replacement for some of the standard library features

## Disclamer
The library is developped mainly for my own use. Use with caution
as it may contain bugs.
Are included "as is" in the project:
  - [fmt](https://github.com/fmtlib/fmt/): since std::format is not quite there yet (imo)
  - [flux](https://github.com/tcbrindle/flux/): a better (imo) implement of ranges in the style of Rust
  - [PPK_ASSERT](https://github.com/fmtlib/fmt/): better asserts

## Usage
I don't provide cmake install scripts, just include the src files in your project,
or as a submodule and in CMakeLists.txt:

```cmake
add_subdirectory(orblib)
...
target_link_libraries(myproject PUBLIC orb::orblib)
```



