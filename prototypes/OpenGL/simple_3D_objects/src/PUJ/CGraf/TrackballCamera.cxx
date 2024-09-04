// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/TrackballCamera.h>

#include <GL/gl.h>

// -------------------------------------------------------------------------
PUJ::CGraf::TrackballCamera::
TrackballCamera( )
  : Superclass( )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::TrackballCamera::
~TrackballCamera( )
{
}

// -------------------------------------------------------------------------
void PUJ::CGraf::TrackballCamera::
rotate( const TReal& da )
{
  this->m_Angle += da;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::TrackballCamera::
load( )
{
  this->Superclass::load( );

  glTranslatef(
    this->m_LookAt[ 0 ], this->m_LookAt[ 1 ], this->m_LookAt[ 2 ]
    );
  glRotatef(
    this->m_Angle,
    this->m_Up[ 0 ], this->m_Up[ 1 ], this->m_Up[ 2 ]
    );
  glTranslatef(
    -this->m_LookAt[ 0 ], -this->m_LookAt[ 1 ], -this->m_LookAt[ 2 ]
    );
}

// eof - $RCSfile$
