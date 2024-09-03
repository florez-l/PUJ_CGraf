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
  using TReal = PUJ::CGraf::TReal;

public:
  class TrackballCamera
    : public PUJ::CGraf::Scene::Camera
  {
  public:
    using Self = TrackballCamera;
    using Superclass = PUJ::CGraf::Scene::Camera;

  public:
    TrackballCamera( )
      : Superclass( )
      {
      }
    virtual ~TrackballCamera( )
      {
      }

    void rotate( const TReal& da )
      {
        this->m_Angle += da;
      }

    virtual void load( )
      {
        this->Superclass::load( );

        glTranslatef( this->m_LookAt[ 0 ], this->m_LookAt[ 1 ], this->m_LookAt[ 2 ] );
        glRotatef( this->m_Angle, this->m_Up[ 0 ], this->m_Up[ 1 ], this->m_Up[ 2 ] );
        glTranslatef( -this->m_LookAt[ 0 ], -this->m_LookAt[ 1 ], -this->m_LookAt[ 2 ] );
      }

  protected:
    TReal m_Angle { 0 };
  };


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

      // Configure camera
      this->m_Camera = new TrackballCamera( );
      this->set_perspective( 45, 1e-2, 100 );
      this->m_Camera->set_position(
        ( this->m_Bounds[ 1 ] - this->m_Bounds[ 0 ] ) * 2.5 + this->m_Bounds[ 0 ],
        ( this->m_Bounds[ 3 ] - this->m_Bounds[ 2 ] ) * 2.5 + this->m_Bounds[ 2 ],
        ( this->m_Bounds[ 5 ] - this->m_Bounds[ 4 ] ) * 2.5 + this->m_Bounds[ 4 ]
        );
      this->m_Camera->look_at(
        ( this->m_Bounds[ 1 ] + this->m_Bounds[ 0 ] ) * 0.5,
        ( this->m_Bounds[ 3 ] + this->m_Bounds[ 2 ] ) * 0.5,
        ( this->m_Bounds[ 5 ] + this->m_Bounds[ 4 ] ) * 0.5
        );
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
  if( Self::s_Scene != nullptr )
    delete Self::s_Scene;
  Self::s_Scene = new Simple3DScene( argc, argv );
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
    dynamic_cast< Simple3DScene::TrackballCamera* >( Self::s_Scene->camera( ) )
      ->rotate( 1 );
    glutPostRedisplay( );
  }
  else if( key == 'd' || key == 'D' )
  {
    dynamic_cast< Simple3DScene::TrackballCamera* >( Self::s_Scene->camera( ) )
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
