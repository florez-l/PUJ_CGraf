// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Viewport.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Viewport::
Viewport(
  const unsigned short& width,
  const unsigned short& height,
  const ColorDeep& color_deep
  )
  : Superclass( width, height, color_deep )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Viewport::
Viewport( const Self& other )
  : Superclass( *( dynamic_cast< const Superclass* >( &other ) ) )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Viewport::
Self& PUJ::CGraf::Viewport::
operator=( const Self& other )
{
  this->Superclass::operator=(
    *( dynamic_cast< const Superclass* >( &other ) )
    );
  return( *this );
}

// -------------------------------------------------------------------------
bool PUJ::CGraf::Viewport::
isInside( const unsigned short& x, const unsigned short& y ) const
{
  return( x >= 0 && y >= 0 && x < this->m_Dims[ 0 ] && y < this->m_Dims[ 1 ] );
}

// -------------------------------------------------------------------------
const float& PUJ::CGraf::Viewport::
get( const unsigned short& x, const unsigned short& y ) const
{
  unsigned long long i = ( ( y * this->m_Dims[ 0 ] ) + x ) * this->m_Dims[ 2 ];
  return( this->m_Buffer[ i ] );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Viewport::
set( const unsigned short& x, const unsigned short& y, const float& v )
{
  unsigned long long i = ( ( y * this->m_Dims[ 0 ] ) + x ) * this->m_Dims[ 2 ];
  this->m_Buffer[ i ] = v;
}

// eof - $RCSfile$
