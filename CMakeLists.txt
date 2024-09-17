## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================
cmake_minimum_required(VERSION 3.10)
project(PUJ_CGraf)

# Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
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

# Output dirs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Find OpenGL and GLUT
cmake_policy(SET CMP0072 OLD)
find_package(OpenGL)
find_package(GLUT)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

# CXX compile options
set (CMAKE_CXX_STANDARD 20)

# Subdirs
subdirs(apps lib)

## Create a static library
#add_library(
#  PUJ_CGraf_Simple3DObjectWithLighs
#  STATIC
#  src/PUJ/CGraf/Camera.cxx
#  src/PUJ/CGraf/Camera.h
#  src/PUJ/CGraf/TrackballCamera.cxx
#  src/PUJ/CGraf/TrackballCamera.h
#  src/PUJ/CGraf/Mesh.cxx
#  src/PUJ/CGraf/Mesh.h
#  src/PUJ/CGraf/Object.cxx
#  src/PUJ/CGraf/Object.h
#  src/PUJ/CGraf/Scene.cxx
#  src/PUJ/CGraf/Scene.h
#  src/PUJ/CGraf/Traits.h
#  )
#target_link_libraries(
#  PUJ_CGraf_Simple3DObjectWithLighs
#  OpenGL::GL  OpenGL::GLU
#  ${Boost_LIBRARIES}
#  )

## Create application
#add_executable(
#  Simple3DObjectWithLighs
#  src/simple_3D_objects_with_lights.cxx
#  src/Application.cxx
#  src/Application.h
#  src/Scene.cxx
#  src/Scene.h
#  )
#target_link_libraries(
#  Simple3DObjectWithLighs PUJ_CGraf_Simple3DObjectWithLighs GLUT::GLUT
#  )

## eof - $RCSfile$