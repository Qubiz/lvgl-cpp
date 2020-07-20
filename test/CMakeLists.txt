if (NOT ZEPHYR_MODULE)
    add_subdirectory(simulator)
endif ()

if (ZEPHYR_TEST)
    add_subdirectory(zephyr)
endif ()