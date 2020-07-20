
if (ZEPHYR_MODULE)
    zephyr_interface_library_named(zephyr-lvgl-display)
    target_link_libraries(zephyr-lvgl-display INTERFACE lvgl-cpp)
    target_include_directories(zephyr-lvgl-display INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()