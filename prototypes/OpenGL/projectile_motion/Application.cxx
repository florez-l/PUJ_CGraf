// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Application.h"

#include <sstream>
#include <GL/glut.h>






#include <iostream>




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
  glutMotionFunc( cbk_motion );
  glutPassiveMotionFunc( cbk_passive_motion );
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

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  Self::s_Scene->update_projection( );

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
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void Application::
cbk_motion( int x, int y )
{
  std::cout << "Motion: " << x << " " << y << std::endl;
}

// -------------------------------------------------------------------------
void Application::
cbk_passive_motion( int x, int y )
{
  std::cout << "PassiveMotion: " << x << " " << y << std::endl;
}

// eof - $RCSfile$
