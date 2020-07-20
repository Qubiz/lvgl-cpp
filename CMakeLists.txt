cmake_minimum_required(VERSION 3.15)

option(ZEPHYR_TEST "Enables testing the zephyr module" OFF)
option(ZEPHYR_MODULE "This enables this project to be used as a Zephyr RTOS module" OFF)

if (ZEPHYR_TEST)
   include(cmake/zephyr/test.cmake)
endif()

if (ZEPHYR_MODULE)
    message(STATUS "Using lvgl-cpp library as Zephyr module...")
endif()

PROJECT(lvgl-cpp CXX C)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(port)
add_subdirectory(test)