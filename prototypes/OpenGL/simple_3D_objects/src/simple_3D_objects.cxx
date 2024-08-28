// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>
#include <PUJ/CGraf/Scene.h>
#include <GL/glut.h>

/**
 */
class Application
{
public:
  using Self = Application;

public:
  static void init( int argc, char** argv );
  static void go( );

private:
  static void cbk_idle( );
  static void cbk_display( );
  static void cbk_keyboard( unsigned char key, int x, int y );
  static void cbk_reshape( int width, int height );

private:
  inline static int s_WindowSize[ 2 ] = { 700, 700 };
  inline static int s_MainWindowId { -1 };

  inline static PUJ::CGraf::Scene* s_Scene { nullptr };
};

// -------------------------------------------------------------------------
int main( int argc, char** argv )
{
  Application::init( argc, argv );
  Application::go( );
  return( EXIT_SUCCESS );
}

// -------------------------------------------------------------------------
void Application::
init( int argc, char** argv )
{
  glutInitWindowSize( Self::s_WindowSize[ 0 ], Self::s_WindowSize[ 1 ] );
  glutInitWindowPosition( 0, 0 );
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
  Self::s_MainWindowId = glutCreateWindow( "window" );

  if( Self::s_Scene != nullptr )
    delete Self::s_Scene;
  Self::s_Scene = new PUJ::CGraf::Scene( argc, argv );
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

// eof - $RCSfile$
