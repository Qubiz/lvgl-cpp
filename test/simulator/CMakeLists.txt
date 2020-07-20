find_package(SDL2 REQUIRED)

add_subdirectory(config)

add_executable(simulator)
target_sources(simulator PRIVATE simulator.cpp)

target_link_libraries(simulator
        PRIVATE sdl-lvgl-display
        PRIVATE pthread)

#target_compile_definitions(simulator
#        PUBLIC USE_MONITOR)