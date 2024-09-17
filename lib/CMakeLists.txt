## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

set(
  _hdr
  PUJ/CGraf/Camera.h
  PUJ/CGraf/Mesh.h
  PUJ/CGraf/Object.h
  PUJ/CGraf/Scene.h
  PUJ/CGraf/TrackballCamera.h
  PUJ/CGraf/Traits.h
  )
set(
  _src
  PUJ/CGraf/Camera.cxx
  PUJ/CGraf/Mesh.cxx
  PUJ/CGraf/Mesh_load_from_OBJ.cxx
  PUJ/CGraf/Object.cxx
  PUJ/CGraf/Scene.cxx
  PUJ/CGraf/TrackballCamera.cxx
  )

# Create a static library
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_library(PUJ_CGraf STATIC ${_hdr} ${_src})
target_link_libraries(PUJ_CGraf OpenGL::GL OpenGL::GLU ${Boost_LIBRARIES})



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