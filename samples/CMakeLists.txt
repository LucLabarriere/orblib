add_executable(sample_result result/main.cpp)
add_executable(sample_box    box/main.cpp)
add_executable(sample_print  print/main.cpp)
add_executable(sample_assert assert/main.cpp)

target_link_libraries(sample_result PRIVATE orb::orblib SYSTEM)
target_link_libraries(sample_box    PRIVATE orb::orblib SYSTEM)
target_link_libraries(sample_print  PRIVATE orb::orblib SYSTEM)
target_link_libraries(sample_assert PRIVATE orb::orblib SYSTEM)
