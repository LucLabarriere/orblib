add_executable(sample_dynlib        main.cpp)
target_link_libraries(sample_dynlib PRIVATE orb::orblib SYSTEM)

add_library(sample_dynlib_testlib           SHARED testlib.cpp)
target_link_libraries(sample_dynlib_testlib PUBLIC orb::orblib SYSTEM)
