if (ZEPHYR_MODULE)
    add_subdirectory(zephyr)
endif ()

if (NOT ZEPHYR_MODULE)
    add_subdirectory(sdl)
endif ()