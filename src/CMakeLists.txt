# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Burndown_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST 
    "${Burndown_SOURCE_DIR}/include/burndown/parser.hpp"
    "${Burndown_SOURCE_DIR}/include/burndown/fileio.hpp"
    )

# Make an automatic library - will be static or dynamic based on user setting
add_library(burndown_library 
    parser.cpp 
    fileio.cpp
    ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(burndown_library PUBLIC ../include)

# This depends on (header only) boost
#target_link_libraries(burndown_library PRIVATE Boost::boost)

# All users of this library will need at least C++14
target_compile_features(burndown_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
