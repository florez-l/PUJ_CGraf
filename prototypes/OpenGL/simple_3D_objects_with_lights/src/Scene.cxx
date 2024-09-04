// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Scene.h"

#include <sstream>

#include <GL/gl.h>

#include <PUJ/CGraf/Mesh.h>
#include <PUJ/CGraf/TrackballCamera.h>

// -------------------------------------------------------------------------
Scene::
Scene( int argc, char** argv )
  : PUJ::CGraf::Scene( argc, argv )
{
  if( argc == 1 )
  {
    std::stringstream err;
    err
      << "Usage: " << argv[ 0 ] << " [file.obj]" << std::endl
      << "You can download some examples from:" << std::endl
      << "****************************************************"
      << std::endl
      << "* https://www.prinmath.com/csci5229/OBJ/index.html *"
      << std::endl
      << "****************************************************"
      << std::endl;
    throw std::invalid_argument( err.str( ) );
  } // end if
  this->m_Model = argv[ 1 ];
}

// -------------------------------------------------------------------------
Scene::
~Scene( )
{
}

// -------------------------------------------------------------------------
void Scene::
init( )
{
  glEnable( GL_LIGHTING );
  this->Superclass::init( );
  glShadeModel( GL_FLAT );
}

// -------------------------------------------------------------------------
void Scene::
_load_scene( )
{
  if( this->m_Root != nullptr )
    delete this->m_Root;

  this->m_Root = new PUJ::CGraf::Object( "root" );

  // Load object
  PUJ::CGraf::Mesh* object = new PUJ::CGraf::Mesh( "object" );
  object->set_drawmode_to_surface( );
  object->load_from_OBJ( this->m_Model );
  object->load_bounding_box( this->m_Bounds );
  this->m_Root->add_child( object, 0, 0, 0 );

  // Configure camera
  this->m_Camera = new PUJ::CGraf::TrackballCamera( );
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

  // Configure ambient light
  glMaterialfv( GL_FRONT, GL_AMBIENT, this->m_AmbientLight );
  glLightfv( GL_LIGHT0, GL_AMBIENT, this->m_AmbientLight );

  // A positional light
  TReal mat_ambient[ 4 ] = { 0.4, 0.4, 0.4, 1 };
  TReal light_position[ 3 ];
  light_position[ 0 ] = ( this->m_Bounds[ 1 ] - this->m_Bounds[ 0 ] ) * 1.5 + this->m_Bounds[ 0 ];
  light_position[ 1 ] = ( this->m_Bounds[ 3 ] - this->m_Bounds[ 2 ] ) * 1.5 + this->m_Bounds[ 2 ];
  light_position[ 2 ] = ( this->m_Bounds[ 5 ] - this->m_Bounds[ 4 ] ) * 1.5 + this->m_Bounds[ 4 ];

  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_ambient );
  glLightfv( GL_LIGHT1, GL_POSITION, light_position );

  // Enable lights
  glEnable( GL_LIGHT0 );
  glEnable( GL_LIGHT1 );
  glEnable( GL_DEPTH_TEST );
}

// eof - $RCSfile$
