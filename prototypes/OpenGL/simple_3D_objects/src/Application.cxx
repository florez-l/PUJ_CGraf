// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Application.h"
#include "Scene.h"

#include <PUJ/CGraf/TrackballCamera.h>

#include <GL/glut.h>

// -------------------------------------------------------------------------
void Application::
init( int argc, char** argv )
{
  if( Self::s_Scene != nullptr )
    delete Self::s_Scene;
  Self::s_Scene = new Scene( argc, argv );
  const int* w = Self::s_Scene->window_size( );

  glutInitWindowSize( w[ 0 ], w[ 1 ] );
  glutInitWindowPosition( 0, 0 );
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

  Self::s_MainWindowId = glutCreateWindow( "window" );
  Self::s_Scene->init( );

  glutIdleFunc( Self::cbk_idle );
  glutDisplayFunc( Self::cbk_display );
  glutKeyboardFunc( Self::cbk_keyboard );
  glutReshapeFunc( Self::cbk_reshape );
}

// -------------------------------------------------------------------------
void Application::
go( )
{
  glutMainLoop( );
}

// -------------------------------------------------------------------------
void Application::
cbk_idle( )
{
  glutPostRedisplay( );
}

// -------------------------------------------------------------------------
void Application::
cbk_display( )
{
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
  }
  else if( key == 'a' || key == 'A' )
  {
    dynamic_cast< PUJ::CGraf::TrackballCamera* >( Self::s_Scene->camera( ) )
      ->rotate( 1 );
    glutPostRedisplay( );
  }
  else if( key == 'd' || key == 'D' )
  {
    dynamic_cast< PUJ::CGraf::TrackballCamera* >( Self::s_Scene->camera( ) )
      ->rotate( -1 );
    glutPostRedisplay( );
  } // end if
}

// -------------------------------------------------------------------------
void Application::
cbk_reshape( int width, int height )
{
  Self::s_Scene->project( width, height );
  glutPostRedisplay( );
}

// eof - $RCSfile$
