cmake_minimum_required(VERSION 3.15)

option(LVGLCPP_TEST "Enables testing" OFF)
option(LVGLCPP_ZEPHYR_TEST "Enables testing the zephyr module" OFF)
option(LVGLCPP_ZEPHYR_MODULE "This enables this project to be used as a Zephyr RTOS module" OFF)
option(LVGLCPP_SIMULATOR_TEST "Enables testing the simulator" OFF)

if (LVGLCPP_ZEPHYR_TEST)
   include(cmake/zephyr/test.cmake)
endif()

if (LVGLCPP_ZEPHYR_MODULE)
    message(STATUS "Using lvgl-cpp library as Zephyr module...")
endif()

PROJECT(lvgl-cpp CXX C)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(port)

if (LVGLCPP_TEST)
    add_subdirectory(test)
endif ()
