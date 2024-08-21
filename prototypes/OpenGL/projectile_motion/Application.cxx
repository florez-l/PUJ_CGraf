// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Application.h"
#include "Helpers.h"

#include <sstream>
#include <GL/glut.h>

// -------------------------------------------------------------------------
void Application::
init( int argc, char** argv )
{
  if( argc > 1 )
    std::istringstream( argv[ 1 ] ) >> Self::s_WorldSize[ 0 ];
  if( argc > 2 )
    std::istringstream( argv[ 2 ] ) >> Self::s_WorldSize[ 1 ];

  glutInitWindowSize( Self::s_WindowSize[ 0 ], Self::s_WindowSize[ 1 ] );
  glutInitWindowPosition( 0, 0 );
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  Self::s_MainWindowId = glutCreateWindow( "window" );

  if( Self::s_Scene != nullptr )
    delete Self::s_Scene;
  Self::s_Scene = new Scene( Self::s_WorldSize[ 0 ], Self::s_WorldSize[ 1 ] );
  Self::s_Scene->init( );

  glutDisplayFunc( Self::cbk_display );
  glutKeyboardFunc( Self::cbk_keyboard );
  glutReshapeFunc( Self::cbk_reshape );
  glutMouseFunc( Self::cbk_mouse );
  glutMotionFunc( Self::cbk_motion );
  glutPassiveMotionFunc( Self::cbk_passive_motion );
}

// -------------------------------------------------------------------------
void Application::
go( )
{
  glutMainLoop( );
}

// -------------------------------------------------------------------------
void Application::
cbk_display( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
  Self::s_Scene->draw( );

  glutSwapBuffers( );
}

// -------------------------------------------------------------------------
void Application::
cbk_keyboard( unsigned char key, int x, int y )
{
  if( key == 27 ) // ESC
  {
    if( Self::s_MainWindowId != -1 )
    {
      glutDestroyWindow( Self::s_MainWindowId );
      Self::s_MainWindowId = -1;
      if( Self::s_Scene != nullptr )
        delete Self::s_Scene;
      Self::s_Scene = nullptr;
    } // end if
  } // end if
}

// -------------------------------------------------------------------------
void Application::
cbk_reshape( int width, int height )
{
  Self::s_WindowSize[ 0 ] = width;
  Self::s_WindowSize[ 1 ] = height;

  glViewport( 0, 0, Self::s_WindowSize[ 0 ], Self::s_WindowSize[ 1 ] );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  Self::s_Scene->project( Self::s_WindowSize[ 0 ], Self::s_WindowSize[ 1 ] );

  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void Application::
cbk_mouse( int button, int state, int x, int y )
{
  if( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
  {
    Self::s_Scene->shift_state( );
    glutPostRedisplay( );
  } // end if
}

// -------------------------------------------------------------------------
void Application::
cbk_motion( int x, int y )
{
}

// -------------------------------------------------------------------------
void Application::
cbk_passive_motion( int x, int y )
{
  static const GLdouble _0 = GLdouble( 0 );
  static const GLdouble _1 = GLdouble( 1 );
  static GLdouble P[ 16 ], Pi[ 16 ], M[ 16 ], Mi[ 16 ];

  glGetDoublev(	GL_MODELVIEW_MATRIX, M );
  glGetDoublev(	GL_PROJECTION_MATRIX, P );
  if( invert_matrix_4x4( M, Mi ) && invert_matrix_4x4( P, Pi ) )
  {
    GLdouble px, py, pz;
    multiply_4x4(
      px, py, pz, Pi,
      ( GLdouble( x << 1 ) / GLdouble( Self::s_WindowSize[ 0 ] ) ) - _1,
      _1 - ( GLdouble( y << 1 ) / GLdouble( Self::s_WindowSize[ 1 ] ) ),
      _0
      );

    GLdouble mx, my, mz;
    multiply_4x4( mx, my, mz, Mi, px, py, pz );

    Self::s_Scene->pick( mx, my );
    glutPostRedisplay( );
  }
  else
  {
    // TODO: report error
  } // end if
}

// eof - $RCSfile$
