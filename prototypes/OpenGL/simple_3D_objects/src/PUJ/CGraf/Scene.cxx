// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Scene.h>
#include <PUJ/CGraf/Object.h>

#include <sstream>

#include <GL/gl.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Scene::
Scene( int argc, char** argv )
{
  /* TODO
     if( argc > 1 )
     std::istringstream( argv[ 1 ] ) >> this->m_Bounds[ 1 ];
     if( argc > 2 )
     std::istringstream( argv[ 2 ] ) >> this->m_Bounds[ 3 ];
     if( argc > 3 )
     std::istringstream( argv[ 3 ] ) >> this->m_Gravity[ 0 ];
     if( argc > 4 )
     std::istringstream( argv[ 4 ] ) >> this->m_Gravity[ 1 ];
     this->m_GravityNorm =
     ( this->m_Gravity[ 0 ] * this->m_Gravity[ 0 ] )
     +
     ( this->m_Gravity[ 1 ] * this->m_Gravity[ 1 ] );
     this->m_GravityNorm = std::sqrt( this->m_GravityNorm );
     this->m_Gravity[ 0 ] /= this->m_GravityNorm;
     this->m_Gravity[ 1 ] /= this->m_GravityNorm;
  */
}

// -------------------------------------------------------------------------
PUJ::CGraf::Scene::
~Scene( )
{
  if( this->m_Root != nullptr )
    delete this->m_Root;
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
  double aw = ( w > h )? ( double( w ) / double( h ) ): double( 1 );
  double ah = ( h > w )? ( double( h ) / double( w ) ): double( 1 );
  glOrtho(
    this->m_Bounds[ 0 ] * aw, this->m_Bounds[ 1 ] * aw,
    this->m_Bounds[ 2 ] * ah, this->m_Bounds[ 3 ] * ah,
    this->m_Bounds[ 4 ], this->m_Bounds[ 5 ]
    );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Scene::
draw( )
{
  this->m_Root->draw( );
}

// eof - $RCSfile$
