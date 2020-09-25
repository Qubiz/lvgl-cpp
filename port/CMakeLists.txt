if (LVGLCPP_ZEPHYR_MODULE)
    add_subdirectory(zephyr)
endif ()

if (NOT LVGLCPP_ZEPHYR_MODULE)
    add_subdirectory(sdl)
endif ()