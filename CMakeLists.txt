
cmake_minimum_required(VERSION 3.21)

# need option for DEBUG_DCG_BUILD

# Set a default build type if none was specified
set(default_build_type "Release")
#if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
#  set(default_build_type "Debug")
#endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release")
  # "MinSizeRel" "RelWithDebInfo"
endif()


project(SFTicks VERSION 0.1 LANGUAGES CXX)

add_executable(sfticks)

# for some resaon numeric values are not passed
# so this is directly set in cmakeconfig.hh
#option(BELTITEM_DISTANCE "Distance between belt items" 120)
configure_file(include/cmakeconfig.hh.in include/cmakeconfig.hh)

target_include_directories(sfticks
  PRIVATE ${SFTicks_SOURCE_DIR}/include
  SYSTEM /usr/local/include
  SYSTEM $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

# checks
include(CheckSymbolExists)
include(CheckCXXSymbolExists)
include(CheckIPOSupported)
# mmap
check_symbol_exists(mmap "sys/mman.h" HAVE_MMAP)
if(NOT HAVE_MMAP)
  message(FATAL_ERROR "mmap is missing")
endif()

# threads
find_package(Threads)
if(NOT Threads_FOUND)
  message(FATAL_ERROR "threading is required")
endif()

# boost
find_package(Boost
  1.72.0
  REQUIRED
  COMPONENTS program_options
)

#zlib
find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
  message(FATAL_ERROR "zlib is required")
endif()

# kqueue
# non-bsd users can try https://github.com/mheily/libkqueue, however this requires code support as well,
# as it is not a drop-in replacement
# mmap
check_symbol_exists(kqueue "sys/event.h" HAVE_KQUEUE)
if(NOT HAVE_KQUEUE)
  message(FATAL_ERROR "kqueue is missing")
endif()

# nlohmann/json - local should be handled differently here, not in a hardcoded way
set(CMAKE_REQUIRED_INCLUDES ";/usr/local/include")
CHECK_INCLUDE_FILE_CXX("nlohmann/json.hpp" HAVE_NLJSON)
if(NOT HAVE_NLJSON)
  message(FATAL_ERROR "nlohmann::json is missing")
endif()

# IPO/LTO check
check_ipo_supported(RESULT LTO_supported OUTPUT error)
if(LTO_supported)
  message(STATUS "Enabling IPO/LTO")
  set_property(TARGET sfticks PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(STATUS "IPO/LTO not supported: <${error}>")
endif()

target_compile_options(sfticks
  PRIVATE -Werror -pedantic -std=c++20 -Wno-c11-extensions -I${Boost_INCLUDE_DIRS}
  $<$<CONFIG:Debug>:-O0 -glldb -ferror-limit=2>
  $<$<CONFIG:Release>:-O2>
)
target_link_options(sfticks
  PRIVATE
  -L/usr/local/lib
  -L${Boost_LIBRARY_DIRS}
  -pthread
  -lboost_program_options
  -lz
)

add_subdirectory(src)
add_subdirectory(include)

set_property(TARGET sfticks PROPERTY CXX_STANDARD 20)
set_property(TARGET sfticks PROPERTY CXX_STANDARD_REQUIRED True)
set_property(TARGET sfticks PROPERTY CXX_EXTENSIONS False)

target_compile_features(sfticks PRIVATE cxx_std_20)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
