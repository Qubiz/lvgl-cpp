add_library(lvgl-config INTERFACE)
target_include_directories(lvgl-config INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(lvgl-config INTERFACE LV_CONF_INCLUDE_SIMPLE)