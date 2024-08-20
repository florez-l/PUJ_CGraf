// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Scene.h"

#include <cmath>
#include <GL/glu.h>
#include <GL/gl.h>

// -------------------------------------------------------------------------
Scene::
Scene( const float& wx, const float& wy )
{
  this->m_WorldBounds[ 0 ] = 0;
  this->m_WorldBounds[ 1 ] = wx;
  this->m_WorldBounds[ 2 ] = 0;
  this->m_WorldBounds[ 3 ] = wy;
}

// -------------------------------------------------------------------------
Scene::
~Scene( )
{
  if( this->m_Root == nullptr )
    delete this->m_Root;
}

// -------------------------------------------------------------------------
void Scene::
init( )
{
  glClearColor(
    this->m_BackgroundColor[ 0 ],
    this->m_BackgroundColor[ 1 ],
    this->m_BackgroundColor[ 2 ],
    this->m_BackgroundColor[ 3 ]
    );

  this->_load_scene( );
}

// -------------------------------------------------------------------------
void Scene::
update_projection( )
{
  gluOrtho2D(
    this->m_WorldBounds[ 0 ], this->m_WorldBounds[ 1 ],
    this->m_WorldBounds[ 2 ], this->m_WorldBounds[ 3 ]
    );
}

// -------------------------------------------------------------------------
void Scene::
draw( )
{
  this->m_Root->draw( );
}

// -------------------------------------------------------------------------
void Scene::
_load_scene( )
{
  if( this->m_Root == nullptr )
    delete this->m_Root;

  this->m_Root = new Object( "root", "none" );

  // World frame
  Object* frame = new Object( "frame", "square" );
  frame->set_color( 0, 0, 0 );
  frame->set_draw_mode_to_wireframe( );
  frame->local_scale( this->m_WorldBounds[ 1 ], this->m_WorldBounds[ 3 ] );
  frame->local_translate( 0.5, 0.5 );
  this->m_Root->add_child( frame, 0, 0 );
  
  // Projectile
  float radius =
    this->m_WorldBounds[ 1 ] * this->m_WorldBounds[ 1 ]
    +
    this->m_WorldBounds[ 3 ] * this->m_WorldBounds[ 3 ];
  radius = std::sqrt( radius ) * 1e-2;

  Object* projectile = new Object( "projectile", "circle" );
  projectile->set_color( 1, 1, 1 );
  projectile->set_draw_mode_to_wireframe( );
  projectile->local_scale( radius, radius );
  frame->add_child( projectile, 0, 0 );
}

// eof - $RCSfile$
