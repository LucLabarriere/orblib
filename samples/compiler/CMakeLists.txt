add_executable(sample_compiler        main.cpp)
target_link_libraries(sample_compiler PRIVATE orb::orblib SYSTEM)

add_library(sample_compiler_testlib           SHARED testlib.cpp)
target_link_libraries(sample_compiler_testlib PUBLIC orb::orblib SYSTEM)
