// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Object.h>

#include <cmath>
#include <GL/gl.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Object::
Object( const std::string& name )
  : m_Name( name )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Object::
~Object( )
{
  for( Object* o: this->m_Children )
    delete o;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_identity( )
{
  this->_identity( this->m_LocalTransformation );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_rotate_X( const TReal& t )
{
  this->_rotate( this->m_LocalTransformation, t, 1, 0, 0 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_rotate_Y( const TReal& t )
{
  this->_rotate( this->m_LocalTransformation, t, 0, 1, 0 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_rotate_Z( const TReal& t )
{
  this->_rotate( this->m_LocalTransformation, t, 0, 0, 1 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_rotate( const TReal& t, const TReal& x, const TReal& y, const TReal& z )
{
  this->_rotate( this->m_LocalTransformation, t, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_scale( const TReal& x, const TReal& y, const TReal& z )
{
  this->_scale( this->m_LocalTransformation, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
local_translate( const TReal& x, const TReal& y, const TReal& z )
{
  this->_translate( this->m_LocalTransformation, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_identity( )
{
  this->_identity( this->m_ParentTransformation );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_rotate_X( const TReal& t )
{
  this->_rotate( this->m_ParentTransformation, t, 1, 0, 0 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_rotate_Y( const TReal& t )
{
  this->_rotate( this->m_ParentTransformation, t, 0, 1, 0 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_rotate_Z( const TReal& t )
{
  this->_rotate( this->m_ParentTransformation, t, 0, 0, 1 );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_rotate( const TReal& t, const TReal& x, const TReal& y, const TReal& z )
{
  this->_rotate( this->m_ParentTransformation, t, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_scale( const TReal& x, const TReal& y, const TReal& z )
{
  this->_scale( this->m_ParentTransformation, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
parent_translate( const TReal& x, const TReal& y, const TReal& z )
{
  this->_translate( this->m_ParentTransformation, x, y, z );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
add_child( Object* child, const TReal& x, const TReal& y, const TReal& z )
{
  if( child != nullptr )
  {
    child->parent_identity( );
    child->parent_translate( x, y, z );
    this->m_Children.push_back( child );
  } // end if
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
visibility_off( )
{
  this->m_Visibility = false;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
visibility_on( )
{
  this->m_Visibility = true;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
draw( ) const
{
  glPushMatrix( );

  glMultMatrixf( this->m_ParentTransformation );

  if( this->m_Visibility )
  {
    glPushMatrix( );

    glMultMatrixf( this->m_LocalTransformation );
    this->_local_draw( );

    glPopMatrix( );
  } // end if

  for( const Object* o: this->m_Children )
    o->draw( );

  glPopMatrix( );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
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
void PUJ::CGraf::Object::
_rotate(
  TReal* M, const TReal& t, const TReal& x, const TReal& y, const TReal& z
  )
{
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
_scale( TReal* M, const TReal& x, const TReal& y, const TReal& z )
{
  /* TODO
     M[ 0 ] *= sx;
     M[ 1 ] *= sx;
     M[ 2 ] *= sx;
     M[ 3 ] *= sx;
     M[ 4 ] *= sy;
     M[ 5 ] *= sy;
     M[ 6 ] *= sy;
     M[ 7 ] *= sy;
  */
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Object::
_translate( TReal* M, const TReal& x, const TReal& y, const TReal& z )
{
  /* TODO
     M[ 12 ] += ( M[ 0 ] * tx ) + ( M[ 4 ] * ty );
     M[ 13 ] += ( M[ 1 ] * tx ) + ( M[ 5 ] * ty );
     M[ 14 ] += ( M[ 2 ] * tx ) + ( M[ 6 ] * ty );
     M[ 15 ] += ( M[ 3 ] * tx ) + ( M[ 7 ] * ty );
  */
}

// eof - $RCSfile$
