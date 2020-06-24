find_package(SDL2 REQUIRED)

add_subdirectory(config)

add_executable(test)
target_sources(test
        PRIVATE test.cpp)

target_link_libraries(test
        PRIVATE lvgl-drivers)

target_compile_definitions(test
        PUBLIC USE_MONITOR)