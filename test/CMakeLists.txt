add_subdirectory(config)

add_executable(test)
target_sources(test PRIVATE test.cpp)
target_link_libraries(test PRIVATE lvgl-cpp)