## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

add_executable(
  PUJ_CGraf_SimpleOBJViewer
  main.cxx
  Application.cxx Application.h
  Scene.cxx Scene.h
  )
target_link_libraries(PUJ_CGraf_SimpleOBJViewer PUJ_CGraf GLUT::GLUT)

## eof - $RCSfile$