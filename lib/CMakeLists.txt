## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

set(
  _hdr
  PUJ/CGraf/Camera.h
  PUJ/CGraf/Mesh.h
  PUJ/CGraf/Object.h
  PUJ/CGraf/Scene.h
  PUJ/CGraf/Texture.h
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
  PUJ/CGraf/Texture.cxx
  PUJ/CGraf/TrackballCamera.cxx
  )

# Create a static library
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_library(PUJ_CGraf STATIC ${_hdr} ${_src})
target_link_libraries(PUJ_CGraf OpenGL::GL OpenGL::GLU ${Boost_LIBRARIES})

## eof - $RCSfile$