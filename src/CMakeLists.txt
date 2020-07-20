add_library(lvgl-cpp INTERFACE)
target_include_directories(lvgl-cpp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lvgl-cpp INTERFACE lvgl)