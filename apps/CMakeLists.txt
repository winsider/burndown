add_executable(burndown main.cpp)

target_compile_features(burndown PRIVATE cxx_std_17)

target_link_libraries(burndown PRIVATE burndown_library)

