## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import sys
from OpenGL.GLUT import *
from OpenGL.GLU import *
from OpenGL.GL import *

'''
'''
bg_color = ( 1, 1, 1, 0 )
main_window_id = None
world_bounds = ( -100, 50, -30, 45 )

'''
'''
def draw_triangle( color = ( 0, 0, 0 ) ):
  glColor3fv( color )

  glBegin( GL_LINES )

  glVertex2f( 0, 0 )
  glVertex2f( 1, 0 )

  glVertex2f( 1, 0 )
  glVertex2f( 0, 1 )

  glVertex2f( 0, 1 )
  glVertex2f( 0, 0 )

  glEnd( )
# end def

'''
'''
def display( ):
  global world_bounds

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )

  glMatrixMode( GL_MODELVIEW )
  glLoadIdentity( )
  glScalef(
    1 / ( world_bounds[ 1 ] - world_bounds[ 0 ] ),
    1 / ( world_bounds[ 3 ] - world_bounds[ 2 ] ),
    1
    )

  glScalef( 10, 10, 1 )
  draw_triangle( )

  glutSwapBuffers( )
# end def

'''
'''
def keyboard( key, x, y ):
  global main_window_id

  if key == b'\x1b': # ESC
    if not main_window_id is None:
      glutDestroyWindow( main_window_id )
    # end if
  # end if
# end def

'''
'''
def main( argv ):
  global main_window_id

  glutInitWindowSize( 700, 700 )
  glutInitWindowPosition( 0, 0 )
  glutInit( argv )
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA )
  main_window_id = glutCreateWindow( 'window' )

  glClearColor( bg_color[ 0 ], bg_color[ 1 ], bg_color[ 2 ], bg_color[ 3 ] )
  glutDisplayFunc( display )
  glutKeyboardFunc( keyboard )

  glutMainLoop( )
# end def

if __name__ == '__main__':
  main( sys.argv )
# end if

## eof - $RCSfile$
