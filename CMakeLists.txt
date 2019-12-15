cmake_minimum_required(VERSION 3.11...3.15)

project(Burndown
    VERSION 0.1
    DESCRIPTION "Burndown - Zero cost abstraction web builder"
    LANGUAGES CXX)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)
endif()

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
	add_subdirectory(docs)
    else()
	message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
#include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
#if(${CMAKE_VERSION} VERSION_LESS 3.14)
#    include(cmake/add_FetchContent_MakeAvailable.cmake)
#endif()

# Accumulator library
# This is header only, so could be replaced with git submodules or FetchContent

# Adds Boost::boost
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS   ON)
#https://stackoverflow.com/questions/58081084/target-boostlibrary-already-has-an-imported-location-link-errors
set(Boost_NO_BOOST_CMAKE    ON) 

if (MSVC)
    find_package(Boost 1.71 REQUIRED)
else()
    find_package(Boost 1.61 REQUIRED program_options)
endif()
message("boost lib: ${Boost_LIBRARIES}")
message("boost inc: ${Boost_INCLUDE_DIR}")

# libsass
find_library(Sass_LIBRARIES NAMES sass libsass PATHS /usr/local/lib ../external/libsass/lib ../libsass/win/bin) 
get_filename_component(Sass_INCLUDE_DIR ../external/libsass/include ABSOLUTE)
message("sass lib: ${Sass_LIBRARIES}")
message("sass inc: ${Sass_INCLUDE_DIR}")

# Formatting library
#FetchContent_Declare(
#  fmtlib
#  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#  GIT_TAG        5.3.0
#)
#FetchContent_MakeAvailable(fmtlib)
# Adds fmt::fmt

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override BURNDOWN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR BURNDOWN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

