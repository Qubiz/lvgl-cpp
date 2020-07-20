 set(ZEPHYR_MODULE ON)

 set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/test/zephyr)
 set(ZEPHYR_TOOLCHAIN_VARIANT gnuarmemb)

 set(NO_BUILD_TYPE_WARNING TRUE)

 message(STATUS "Trying to find the Zephyr package...")
 find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})