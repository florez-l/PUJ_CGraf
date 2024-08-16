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
  if( primitive == "triangle" )
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
    float _2pi = 8.0 * std::atan( 1.0 );
    float k = _2pi / float( samples );
    for( unsigned short i = 0; i < samples; ++i )
    {
      float w = float( i ) * k;
      this->m_Points.push_back( std::cos( w ) );
      this->m_Points.push_back( std::sin( w ) );
    } // end for
  } // end if
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
set_color( float r, float g, float b )
{
  this->m_Color[ 0 ] = r;
  this->m_Color[ 1 ] = g;
  this->m_Color[ 2 ] = b;
}

// -------------------------------------------------------------------------
void Object::
set_color( const std::array< float, 3 >& c )
{
  this->m_Color = c;
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
local_rotate( float t )
{
  this->_rotate( this->m_LocalTransformation, t );
}

// -------------------------------------------------------------------------
void Object::
local_scale( float sx, float sy )
{
  this->_scale( this->m_LocalTransformation, sx, sy );
}

// -------------------------------------------------------------------------
void Object::
local_translate( float tx, float ty )
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
parent_rotate( float t )
{
  this->_rotate( this->m_ParentTransformation, t );
}

// -------------------------------------------------------------------------
void Object::
parent_scale( float sx, float sy )
{
  this->_scale( this->m_ParentTransformation, sx, sy );
}

// -------------------------------------------------------------------------
void Object::
parent_translate( float tx, float ty )
{
  this->_translate( this->m_ParentTransformation, tx, ty );
}

// -------------------------------------------------------------------------
void Object::
add_child( Object* child, float px, float py )
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
draw( ) const
{
  // std::cout << this->m_Name << std::endl;

  glPushMatrix( );
  glMultMatrixf( this->m_ParentTransformation.data( ) );

  glPushMatrix( );
  glMultMatrixf( this->m_LocalTransformation.data( ) );
  glColor3fv( this->m_Color.data( ) );
  glBegin( this->m_DrawMode );
  {
    for( unsigned int i = 0; i < this->m_Points.size( ); i += 2 )
      glVertex2fv( this->m_Points.data( ) + i );
  }
  glEnd( );
  glPopMatrix( );

  for( const Object* o: this->m_Children )
    o->draw( );

  glPopMatrix( );
}

// -------------------------------------------------------------------------
void Object::
_identity( std::array< float, 16 >& M )
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
_rotate( std::array< float, 16 >& M, float t )
{
  /* TODO
     float ct = std::cos( t );
     float st = std::sin( t );
     float a = M[  0 ];
     float b = M[  1 ];
     float e = M[  4 ];
     float f = M[  5 ];
     float i = M[  8 ];
     float j = M[  9 ];
     float m = M[ 12 ];
     float n = M[ 13 ];

     M[  0 ] = ( b * st ) + ( a * ct );
     M[  1 ] = ( b * ct ) - ( a * st );
     M[  4 ] = ( f * st ) + ( e * ct );
     M[  5 ] = ( f * ct ) - ( e * st );
     M[  8 ] = ( j * st ) + ( i * ct );
     M[  9 ] = ( j * ct ) - ( i * st );
     M[ 12 ] = ( n * st ) + ( m * ct );
     M[ 13 ] = ( n * ct ) - ( m * st );
  */
}

// -------------------------------------------------------------------------
void Object::
_scale( std::array< float, 16 >& M, float sx, float sy )
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
_translate( std::array< float, 16 >& M, float tx, float ty )
{
  M[ 12 ] += ( M[ 0 ] * tx ) + ( M[ 4 ] * ty );
  M[ 13 ] += ( M[ 1 ] * tx ) + ( M[ 5 ] * ty );
  M[ 14 ] += ( M[ 2 ] * tx ) + ( M[ 6 ] * ty );
  M[ 15 ] += ( M[ 3 ] * tx ) + ( M[ 7 ] * ty );
}

// eof - $RCSfile$
