if (NOT LVGLCPP_ZEPHYR_MODULE AND LVGLCPP_SIMULATOR_TEST)
    add_subdirectory(simulator)
endif ()

if (LVGLCPP_ZEPHYR_TEST)
    add_subdirectory(zephyr)
endif ()