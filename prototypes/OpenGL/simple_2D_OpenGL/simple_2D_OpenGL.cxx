// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <array>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

/**
 */
int main_window_id = -1;
std::array< float, 4 > bg_color( { 1, 1, 1, 0 } );

/**
 */
void draw_triangle( const std::array< float, 3 >& color = { 0, 0, 0 } )
{
  glColor3fv( color.data( ) );

  glBegin( GL_LINES );
  {
    glVertex2f( 0, 0 );
    glVertex2f( 1, 0 );

    glVertex2f( 1, 0 );
    glVertex2f( 0, 1 );

    glVertex2f( 0, 1 );
    glVertex2f( 0, 0 );
  }
  glEnd( );
}

/**
 */
void display( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  draw_triangle( );

  glutSwapBuffers( );
}

/**
 */
void keyboard( unsigned char key, int x, int y )
{
  if( key == 27 ) // ESC
  {
    if( main_window_id != -1 )
      glutDestroyWindow( main_window_id );
  } // end if
}

/**
 */
int main( int argc, char** argv )
{
  glutInitWindowSize( 700, 700 );
  glutInitWindowPosition( 0, 0 );
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  main_window_id = glutCreateWindow( "window" );

  glClearColor( bg_color[ 0 ], bg_color[ 1 ], bg_color[ 2 ], bg_color[ 3 ] );
  glutDisplayFunc( display );
  glutKeyboardFunc( keyboard );

  glutMainLoop( );

  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
