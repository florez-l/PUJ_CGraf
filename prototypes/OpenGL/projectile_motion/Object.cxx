// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Object.h"

#include <cmath>
#include <GL/gl.h>

// -------------------------------------------------------------------------
Object::
Object(
  const std::string& name, const std::string& primitive, unsigned int samples
  )
  : m_Name( name )
{
  if( primitive == "line" )
  {
    this->m_Points.push_back( 0 );
    this->m_Points.push_back( 0 );
    this->m_Points.push_back( 1 );
    this->m_Points.push_back( 1 );
    this->set_draw_mode( GL_LINES );
  }
  else if( primitive == "triangle" )
  {
    this->m_Points.push_back( -0.5 );
    this->m_Points.push_back( -0.28867513459 );
    this->m_Points.push_back(  0.5 );
    this->m_Points.push_back( -0.28867513459 );
    this->m_Points.push_back(  0 );
    this->m_Points.push_back(  0.57735026919 );
  }
  else if( primitive == "square" )
  {
    this->m_Points.push_back( -0.5 );
    this->m_Points.push_back( -0.5 );
    this->m_Points.push_back(  0.5 );
    this->m_Points.push_back( -0.5 );
    this->m_Points.push_back(  0.5 );
    this->m_Points.push_back(  0.5 );
    this->m_Points.push_back( -0.5 );
    this->m_Points.push_back(  0.5 );
  }
  else if( primitive == "circle" )
  {
    TReal _2pi = 8.0 * std::atan( 1.0 );
    TReal k = _2pi / TReal( samples );
    for( unsigned short i = 0; i < samples; ++i )
    {
      TReal w = TReal( i ) * k;
      this->m_Points.push_back( std::cos( w ) );
      this->m_Points.push_back( std::sin( w ) );
    } // end for
  } // end if

  this->m_Points.shrink_to_fit( );
}

// -------------------------------------------------------------------------
Object::
~Object( )
{
  for( Object* o: this->m_Children )
    delete o;
}

// -------------------------------------------------------------------------
void Object::
set_color( const TReal& r, const TReal& g, const TReal& b )
{
  this->m_Color[ 0 ] = r;
  this->m_Color[ 1 ] = g;
  this->m_Color[ 2 ] = b;
}

// -------------------------------------------------------------------------
void Object::
set_color( const TReal* c )
{
  this->m_Color[ 0 ] = c[ 0 ];
  this->m_Color[ 1 ] = c[ 1 ];
  this->m_Color[ 2 ] = c[ 2 ];
}

// -------------------------------------------------------------------------
void Object::
set_draw_mode( int mode )
{
  this->m_DrawMode = mode;
}

// -------------------------------------------------------------------------
void Object::
set_draw_mode_to_polygon( )
{
  this->set_draw_mode( GL_POLYGON );
}

// -------------------------------------------------------------------------
void Object::
set_draw_mode_to_wireframe( )
{
  this->set_draw_mode( GL_LINE_LOOP );
}

// -------------------------------------------------------------------------
void Object::
local_identity( )
{
  this->_identity( this->m_LocalTransformation );
}

// -------------------------------------------------------------------------
void Object::
local_rotate( const TReal& t )
{
  this->_rotate( this->m_LocalTransformation, t );
}

// -------------------------------------------------------------------------
void Object::
local_scale( const TReal& sx, const TReal& sy )
{
  this->_scale( this->m_LocalTransformation, sx, sy );
}

// -------------------------------------------------------------------------
void Object::
local_translate( const TReal& tx, const TReal& ty )
{
  this->_translate( this->m_LocalTransformation, tx, ty );
}

// -------------------------------------------------------------------------
void Object::
parent_identity( )
{
  this->_identity( this->m_ParentTransformation );
}

// -------------------------------------------------------------------------
void Object::
parent_rotate( const TReal& t )
{
  this->_rotate( this->m_ParentTransformation, t );
}

// -------------------------------------------------------------------------
void Object::
parent_scale( const TReal& sx, const TReal& sy )
{
  this->_scale( this->m_ParentTransformation, sx, sy );
}

// -------------------------------------------------------------------------
void Object::
parent_translate( const TReal& tx, const TReal& ty )
{
  this->_translate( this->m_ParentTransformation, tx, ty );
}

// -------------------------------------------------------------------------
void Object::
add_child( Object* child, const TReal& px, const TReal& py )
{
  if( child != nullptr )
  {
    child->parent_identity( );
    child->parent_translate( px, py );
    this->m_Children.push_back( child );
  } // end if
}

// -------------------------------------------------------------------------
void Object::
visibility_off( )
{
  this->m_Visibility = false;
}

// -------------------------------------------------------------------------
void Object::
visibility_on( )
{
  this->m_Visibility = true;
}

// -------------------------------------------------------------------------
void Object::
draw( ) const
{
  glPushMatrix( );
  glMultMatrixf( this->m_ParentTransformation );

  if( this->m_Visibility )
  {
    glPushMatrix( );
    glMultMatrixf( this->m_LocalTransformation );

    glColor3fv( this->m_Color );
    glBegin( this->m_DrawMode );
    {
      for( unsigned int i = 0; i < this->m_Points.size( ); i += 2 )
        glVertex2fv( this->m_Points.data( ) + i );
    }
    glEnd( );
    glPopMatrix( );
  } // end if

  for( const Object* o: this->m_Children )
    o->draw( );

  glPopMatrix( );
}

// -------------------------------------------------------------------------
void Object::
set_point( const unsigned int& id, const TReal& x, const TReal& y )
{
  unsigned int p = ( id << 1 );
  if( p < this->m_Points.size( ) )
  {
    this->m_Points[ p ] = x;
    this->m_Points[ p + 1 ] = y;
  } // end if
}

// -------------------------------------------------------------------------
void Object::
_identity( TReal* M )
{
  M[  0 ] = 1;
  M[  1 ] = 0;
  M[  2 ] = 0;
  M[  3 ] = 0;
  M[  4 ] = 0;
  M[  5 ] = 1;
  M[  6 ] = 0;
  M[  7 ] = 0;
  M[  8 ] = 0;
  M[  9 ] = 0;
  M[ 10 ] = 1;
  M[ 11 ] = 0;
  M[ 12 ] = 0;
  M[ 13 ] = 0;
  M[ 14 ] = 0;
  M[ 15 ] = 1;
}

// -------------------------------------------------------------------------
void Object::
_rotate( TReal* M, const TReal& t )
{
}

// -------------------------------------------------------------------------
void Object::
_scale( TReal* M, const TReal& sx, const TReal& sy )
{
  M[ 0 ] *= sx;
  M[ 1 ] *= sx;
  M[ 2 ] *= sx;
  M[ 3 ] *= sx;
  M[ 4 ] *= sy;
  M[ 5 ] *= sy;
  M[ 6 ] *= sy;
  M[ 7 ] *= sy;
}

// -------------------------------------------------------------------------
void Object::
_translate( TReal* M, const TReal& tx, const TReal& ty )
{
  M[ 12 ] += ( M[ 0 ] * tx ) + ( M[ 4 ] * ty );
  M[ 13 ] += ( M[ 1 ] * tx ) + ( M[ 5 ] * ty );
  M[ 14 ] += ( M[ 2 ] * tx ) + ( M[ 6 ] * ty );
  M[ 15 ] += ( M[ 3 ] * tx ) + ( M[ 7 ] * ty );
}

// eof - $RCSfile$
