add_subdirectory(config)
target_sources(app PRIVATE main.cpp)
target_link_libraries(app PRIVATE zephyr-lvgl-display)