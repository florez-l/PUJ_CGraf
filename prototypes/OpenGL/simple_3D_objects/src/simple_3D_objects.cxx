// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>

#include <PUJ/CGraf/Object.h>
#include <PUJ/CGraf/Mesh.h>
#include <PUJ/CGraf/Scene.h>

#include <GL/glut.h>

/**
 */
class Simple3DScene
  : public PUJ::CGraf::Scene
{
public:
  Simple3DScene( int argc, char** argv )
    : PUJ::CGraf::Scene( argc, argv )
    {
    }
  virtual ~Simple3DScene( ) = default;

protected:
  virtual void _load_scene( ) override
    {
      if( this->m_Root != nullptr )
        delete this->m_Root;

      this->m_Root = new PUJ::CGraf::Object( "root" );

      // Load room
      PUJ::CGraf::Mesh* room = new PUJ::CGraf::Mesh( "room" );
      room->set_drawmode_to_wireframe( );
      room->load_from_OBJ( "./res/room.obj" );
      room->load_bounding_box( this->m_Bounds );

      this->m_Root->add_child( room, 0, 0, 0 );

      // World frame
      /* TODO
         this->m_Frame = new Object( "frame", "square" );
         this->m_Frame->set_color( 1, 1, 1 );
         this->m_Frame->set_draw_mode_to_wireframe( );
         this->m_Frame->local_scale(
         this->m_Bounds[ 1 ] - this->m_Bounds[ 0 ],
         this->m_Bounds[ 3 ] - this->m_Bounds[ 2 ]
         );
         this->m_Frame->local_translate( 0.5, 0.5 );
         this->m_Root->add_child( this->m_Frame, 0, 0 );
  
         // Projectile
         this->m_Radius =
         ( this->m_Bounds[ 1 ] * this->m_Bounds[ 1 ] ) +
         ( this->m_Bounds[ 3 ] * this->m_Bounds[ 3 ] );
         this->m_Radius = std::sqrt( this->m_Radius ) * 1e-2;

         this->m_Projectile = new Object( "projectile", "circle" );
         this->m_Projectile->set_color( 1, 1, 1 );
         this->m_Projectile->set_draw_mode_to_wireframe( );
         this->m_Projectile->local_scale( this->m_Radius, this->m_Radius );
         this->m_Frame->add_child(
         this->m_Projectile,
         ( this->m_Bounds[ 1 ] - this->m_Bounds[ 0 ] ) * 0.5 + this->m_Bounds[ 0 ],
         ( this->m_Bounds[ 3 ] - this->m_Bounds[ 2 ] ) * 0.5 + this->m_Bounds[ 2 ]
         );
         
         // Aim line
         this->m_AimLine = new Object( "aim_line", "line" );
         this->m_AimLine->set_color( 1, 1, 1 );
         this->m_AimLine->visibility_off( );
         this->m_Root->add_child( this->m_AimLine, 0, 0 );
      */
    }
};


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

  inline static Simple3DScene* s_Scene { nullptr };
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
  Self::s_Scene = new Simple3DScene( argc, argv );
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
