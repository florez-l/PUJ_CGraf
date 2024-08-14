// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <array>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

/**
 */
int main_window_id = -1;
std::array< float, 4 > bg_color( { 1, 1, 1, 0 } );
std::array< int, 2 > window_size( { 700, 700 } );
std::array< float, 4 > world_bounds( { -100, 50, -70, 45 } );

/**
 */
void draw_orthobase( )
{
  glColor3f( 1, 0, 0 );
  glBegin( GL_LINES );
  {
    glVertex2f( -0.1, 0 );
    glVertex2f(  1  , 0 );
  }
  glEnd( );

  glColor3f( 0, 1, 0 );
  glBegin( GL_LINES );
  {
    glVertex2f( 0, -0.1 );
    glVertex2f( 0,  1 );
  }
  glEnd( );
}

/**
 */
void draw_triangle(
  const std::array< float, 3 >& color = { 0, 0, 0 },
  const bool& filled = false
  )
{
  glColor3fv( color.data( ) );

  glBegin( ( filled )? GL_POLYGON: GL_LINE_LOOP );
  {
    glVertex2f( -0.5, -0.28867513459 );
    glVertex2f(  0.5, -0.28867513459 );
    glVertex2f(  0  ,  0.57735026919 );
  }
  glEnd( );
}

/**
 */
void draw_square(
  const std::array< float, 3 >& color = { 0, 0, 0 },
  const bool& filled = false
  )
{
  glColor3fv( color.data( ) );

  glBegin( ( filled )? GL_POLYGON: GL_LINE_LOOP );
  {
    glVertex2f( -0.5, -0.5 );
    glVertex2f(  0.5, -0.5 );
    glVertex2f(  0.5,  0.5 );
    glVertex2f( -0.5,  0.5 );
  }
  glEnd( );
}

/**
 */
void draw_circle(
  const std::array< float, 3 >& color = { 0, 0, 0 },
  const bool& filled = false,
  const unsigned short& samples = 100
  )
{
  static const float _2pi = 8.0 * std::atan( 1.0 );

  glColor3fv( color.data( ) );

  float k = _2pi / float( samples );
  glBegin( ( filled )? GL_POLYGON: GL_LINE_LOOP );
  {
    for( unsigned short i = 0; i < samples; ++i )
    {
      float w = float( i ) * k;
      glVertex2f( std::cos( w ), std::sin( w ) );
    } // end for
  }
  glEnd( );
}

/**
 */
void display( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  draw_orthobase( );
  draw_triangle( { 0, 0, 0 } );
  draw_square( { 1, 0, 0 } );
  draw_circle( { 1, 0, 1 } );

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
  glutInitWindowSize( window_size[ 0 ], window_size[ 1 ] );
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
