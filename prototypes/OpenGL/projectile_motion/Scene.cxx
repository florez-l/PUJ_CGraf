// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Scene.h"

#include <cmath>
#include <GL/gl.h>

// -------------------------------------------------------------------------
Scene::
Scene( const float& wx, const float& wy )
{
  this->m_Bounds[ 0 ] = 0;
  this->m_Bounds[ 1 ] = wx;
  this->m_Bounds[ 2 ] = 0;
  this->m_Bounds[ 3 ] = wy;
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
    this->m_Background[ 0 ],
    this->m_Background[ 1 ],
    this->m_Background[ 2 ],
    this->m_Background[ 3 ]
    );

  this->_load_scene( );
}

// -------------------------------------------------------------------------
void Scene::
project( const int& w, const int& h )
{
  double aw = ( w > h )? ( double( w ) / double( h ) ): double( 1 );
  double ah = ( h > w )? ( double( h ) / double( w ) ): double( 1 );
  glOrtho(
    this->m_Bounds[ 0 ] * aw, this->m_Bounds[ 1 ] * aw,
    this->m_Bounds[ 2 ] * ah, this->m_Bounds[ 3 ] * ah,
    -1, 1
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
pick( const float& x, const float& y )
{
  if( this->m_State != Self::FIRE )
  {
    if(
      x >= ( this->m_Bounds[ 0 ] + this->m_Radius )
      &&
      x <= ( this->m_Bounds[ 1 ] - this->m_Radius )
      &&
      y >= ( this->m_Bounds[ 2 ] + this->m_Radius )
      &&
      y <= ( this->m_Bounds[ 3 ] - this->m_Radius )
      )
    {
      if( this->m_State == Self::LOCALIZE )
      {
        this->m_Projectile->parent_identity( );
        this->m_Projectile->parent_translate( x, y );
        this->m_AimLine->set_point( 0, x, y );
        this->m_AimLine->set_point( 1, x, y );
      }
      else if( this->m_State == Self::AIM )
        this->m_AimLine->set_point( 1, x, y );
    } // end if
  } // end if
}

// -------------------------------------------------------------------------
void Scene::
shift_state( )
{
  if( this->m_State == Self::LOCALIZE )
  {
    this->m_State = Self::AIM;
    this->m_AimLine->visibility_on( );
  }
  else if( this->m_State == Self::AIM )
    this->m_State = Self::FIRE;
}

// -------------------------------------------------------------------------
void Scene::
_load_scene( )
{
  if( this->m_Root == nullptr )
    delete this->m_Root;

  this->m_Root = new Object( "root", "none" );

  // World frame
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
}

// eof - $RCSfile$
