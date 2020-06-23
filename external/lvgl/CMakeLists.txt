add_library(lvgl)

FILE(GLOB_RECURSE SOURCES lvgl/src/*.c)

target_sources(lvgl PRIVATE ${SOURCES})
target_include_directories(lvgl INTERFACE lvgl)
target_link_libraries(lvgl PUBLIC lvgl-config)