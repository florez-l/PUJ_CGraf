## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================
cmake_minimum_required(VERSION 3.10)
project(simple_3D_objects)

# Find OpenGL and GLUT
cmake_policy(SET CMP0072 OLD)
find_package(OpenGL)
find_package(GLUT)

# CXX compile options
set (CMAKE_CXX_STANDARD 20)
include_directories(src)

# Create a static library
add_library(
  PUJ_CGraf_Simple3DObject
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
target_link_libraries(PUJ_CGraf_Simple3DObject OpenGL::GL  OpenGL::GLU)

# Create application
add_executable(
  Simple3DObject
  src/simple_3D_objects.cxx
  src/Application.cxx
  src/Application.h
  src/Scene.cxx
  src/Scene.h
  )
target_link_libraries(Simple3DObject PUJ_CGraf_Simple3DObject GLUT::GLUT)

## eof - $RCSfile$