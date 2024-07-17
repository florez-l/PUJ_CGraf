## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

# -- Base configuration
cmake_minimum_required(VERSION 3.0)
project(PUJ_CGraf_prototypes VERSION 0.0.0.0)

# -- Set a default build type if none was specified
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(
    CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE
    )
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
    )
endif()

# -- Output dirs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# -- Language version
set(CMAKE_CXX_STANDARD 20)

# -- Base library
include_directories(
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )
set(
  _lib_src
  ${PROJECT_SOURCE_DIR}/PUJ/CGraf/FrameBuffer.cxx
  ${PROJECT_SOURCE_DIR}/PUJ/CGraf/FrameBuffer.h
  )
add_library(PUJ_CGraf STATIC ${_lib_src})
target_link_libraries(PUJ_CGraf stdc++fs)

# -- Executables
set(
  _execs
  01_random_frame
  02_morphing_frames
  )
foreach(_e ${_execs})
  add_executable(${_e} executables/${_e}.cxx)
  target_link_libraries(${_e} PUJ_CGraf)
endforeach()

## eof - $RCSfile$
