// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Camera.h>
#include <GL/glu.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Camera::
Camera( )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Camera::
~Camera( )
{
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Camera::
set_position( const TReal& x, const TReal& y, const TReal& z )
{
  this->m_Position[ 0 ] = x;
  this->m_Position[ 1 ] = y;
  this->m_Position[ 2 ] = z;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Camera::
look_at( const TReal& x, const TReal& y, const TReal& z )
{
  this->m_LookAt[ 0 ] = x;
  this->m_LookAt[ 1 ] = y;
  this->m_LookAt[ 2 ] = z;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Camera::
load( )
{
  gluLookAt(
    this->m_Position[ 0 ], this->m_Position[ 1 ], this->m_Position[ 2 ],
    this->m_LookAt[ 0 ], this->m_LookAt[ 1 ], this->m_LookAt[ 2 ],
    this->m_Up[ 0 ], this->m_Up[ 1 ], this->m_Up[ 2 ]
    );
}

// eof - $RCSfile$
