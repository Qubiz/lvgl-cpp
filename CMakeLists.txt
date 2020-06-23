cmake_minimum_required(VERSION 3.15)

PROJECT(lvgl-cpp CXX C)

include(cmake/StandardProjectSettings.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/Cache.cmake)
include(cmake/StaticAnalyzers.cmake)

add_library(PROJECT_OPTIONS INTERFACE)
target_compile_features(PROJECT_OPTIONS INTERFACE cxx_std_17)
enable_sanitizers(PROJECT_OPTIONS)

add_library(PROJECT_WARNINGS INTERFACE)
set_project_warnings(PROJECT_WARNINGS)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(test)