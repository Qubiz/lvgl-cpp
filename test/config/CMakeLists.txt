find_package(SDL2 REQUIRED)

add_library(lvgl-config INTERFACE)
target_include_directories(lvgl-config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(lvgl-config
        INTERFACE LV_CONF_INCLUDE_SIMPLE
        INTERFACE USE_MONITOR)
target_link_libraries(lvgl-config INTERFACE ${SDL2_LIBRARIES})