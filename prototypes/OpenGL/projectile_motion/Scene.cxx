// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Scene.h"

#include <GL/glu.h>
#include <GL/gl.h>

// -------------------------------------------------------------------------
Scene::
Scene( )
{
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

  // Floor
  Object* floor = new Object( "floor", "square" );
  floor->set_color( 0, 0, 0 );
  floor->set_draw_mode_to_polygon( );
  floor->local_scale( 15, 0.3 );
  floor->local_translate( 0.5, 0.5 );
  this->m_Root->add_child( floor, 0, 0 );

  // House
  Object* house = new Object( "house", "square" );
  house->set_color( 0.4, 0.4, 0.4 );
  house->set_draw_mode_to_polygon( );
  house->local_scale( 2.5, 3 );
  house->local_translate( 0.5, 0.5 );
  floor->add_child( house, 2, 0.3 );

  // Ceiling
  Object* ceiling = new Object( "ceiling", "triangle" );
  ceiling->set_color( 1, 0, 0 );
  ceiling->set_draw_mode_to_polygon( );
  ceiling->local_scale( 4.5, 2 );
  ceiling->local_translate( 0, 0.28867513459 );
  house->add_child( ceiling, 1.25, 3 );

  // Window1
  Object* window1 = new Object( "window1", "square" );
  window1->set_color( 1, 1, 1 );
  window1->set_draw_mode_to_polygon( );
  window1->local_scale( 0.4, 0.4 );
  window1->local_translate( 0.5, 0.5 );
  house->add_child( window1, 0.75, 2 );

  // Window2
  Object* window2 = new Object( "window2", "square" );
  window2->set_color( 1, 1, 1 );
  window2->set_draw_mode_to_polygon( );
  window2->local_scale( 0.4, 0.4 );
  window2->local_translate( 0.5, 0.5 );
  house->add_child( window2, 1.75, 1.75 );

  // Door
  Object* door = new Object( "door", "square" );
  door->set_color( 1, 0.64, 0 );
  door->set_draw_mode_to_polygon( );
  door->local_scale( 1, 1.5 );
  door->local_translate( 0, 0.5 );
  house->add_child( door, 1.25, 0 );
}

// eof - $RCSfile$
