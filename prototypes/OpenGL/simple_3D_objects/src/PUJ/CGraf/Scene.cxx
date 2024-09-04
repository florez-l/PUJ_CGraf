// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Scene.h>
#include <PUJ/CGraf/Camera.h>
#include <PUJ/CGraf/Object.h>

#include <limits>
#include <sstream>

#include <GL/gl.h>
#include <GL/glu.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Scene::
Scene( int argc, char** argv )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Scene::
~Scene( )
{
  if( this->m_Root != nullptr )
    delete this->m_Root;
  if( this->m_Camera != nullptr )
    delete this->m_Camera;
}

// -------------------------------------------------------------------------
const int* PUJ::CGraf::Scene::
window_size( ) const
{
  return( &( this->m_WindowSize[ 0 ] ) );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Scene::
set_ortho(
  const TReal& left, const TReal& right,
  const TReal& bottom, const TReal& up,
  const TReal& near, const TReal& far
  )
{
  this->m_UsePerspective = false;
  this->m_Ortho[ 0 ] = left;
  this->m_Ortho[ 1 ] = right;
  this->m_Ortho[ 2 ] = bottom;
  this->m_Ortho[ 3 ] = up;
  this->m_Ortho[ 4 ] = near;
  this->m_Ortho[ 5 ] = far;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Scene::
set_perspective( const TReal& fovy, const TReal& near, const TReal& far )
{
  this->m_UsePerspective = true;
  this->m_Perspective[ 0 ] = fovy;
  this->m_Perspective[ 1 ] = near;
  this->m_Perspective[ 2 ] = far;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Scene::
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
void PUJ::CGraf::Scene::
project( const int& w, const int& h )
{
  this->m_WindowSize[ 0 ] = w;
  this->m_WindowSize[ 1 ] = h;

  glViewport( 0, 0, this->m_WindowSize[ 0 ], this->m_WindowSize[ 1 ] );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  if( this->m_UsePerspective )
    gluPerspective(
      this->m_Perspective[ 0 ],
      TReal( this->m_WindowSize[ 0 ] )
      /
      (
        TReal( this->m_WindowSize[ 1 ] )
        +
        std::numeric_limits< TReal >::epsilon( )
        ),
      this->m_Perspective[ 1 ],
      this->m_Perspective[ 2 ]
      );
  else
    glOrtho(
      this->m_Ortho[ 0 ], this->m_Ortho[ 1 ],
      this->m_Ortho[ 2 ], this->m_Ortho[ 3 ],
      this->m_Ortho[ 4 ], this->m_Ortho[ 5 ]
      );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Scene::
draw( )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  if( this->m_Camera != nullptr )
    this->m_Camera->load( );
  if( this->m_Root != nullptr )
    this->m_Root->draw( );
}

// eof - $RCSfile$
