
add_library(sdl-lvgl-display INTERFACE)
target_link_libraries(sdl-lvgl-display INTERFACE lvgl-cpp)
target_include_directories(sdl-lvgl-display INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
