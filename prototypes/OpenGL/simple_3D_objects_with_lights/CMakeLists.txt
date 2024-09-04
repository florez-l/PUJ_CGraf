## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================
cmake_minimum_required(VERSION 3.10)
project(simple_3D_objects_with_lights)

# Find OpenGL and GLUT
cmake_policy(SET CMP0072 OLD)
find_package(OpenGL)
find_package(GLUT)
find_package(Boost)

# CXX compile options
set (CMAKE_CXX_STANDARD 20)
include_directories(
  ${Boost_INCLUDE_DIRS}
  src
  )

# Create a static library
add_library(
  PUJ_CGraf_Simple3DObjectWithLighs
  STATIC
  src/PUJ/CGraf/Camera.cxx
  src/PUJ/CGraf/Camera.h
  src/PUJ/CGraf/TrackballCamera.cxx
  src/PUJ/CGraf/TrackballCamera.h
  src/PUJ/CGraf/Mesh.cxx
  src/PUJ/CGraf/Mesh.h
  src/PUJ/CGraf/Object.cxx
  src/PUJ/CGraf/Object.h
  src/PUJ/CGraf/Scene.cxx
  src/PUJ/CGraf/Scene.h
  src/PUJ/CGraf/Traits.h
  )
target_link_libraries(
  PUJ_CGraf_Simple3DObjectWithLighs
  OpenGL::GL  OpenGL::GLU
  ${Boost_LIBRARIES}
  )

# Create application
add_executable(
  Simple3DObjectWithLighs
  src/simple_3D_objects_with_lights.cxx
  src/Application.cxx
  src/Application.h
  src/Scene.cxx
  src/Scene.h
  )
target_link_libraries(
  Simple3DObjectWithLighs PUJ_CGraf_Simple3DObjectWithLighs GLUT::GLUT
  )

## eof - $RCSfile$