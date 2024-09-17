// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Mesh.h>
#include <GL/gl.h>

// -------------------------------------------------------------------------
PUJ::CGraf::Mesh::
Mesh( const std::string& name )
  : Superclass( name )
{
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_drawmode_to_points( )
{
  this->m_DrawMode = Self::Points;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_drawmode_to_wireframe( )
{
  this->m_DrawMode = Self::Wireframe;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_drawmode_to_surface( )
{
  this->m_DrawMode = Self::Surface;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_drawmode_to_surface_with_wireframe( )
{
  this->m_DrawMode = Self::SurfaceWithWireframe;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_color( const TReal& r, const TReal& g, const TReal& b )
{
  this->m_Color[ 0 ] = r;
  this->m_Color[ 1 ] = g;
  this->m_Color[ 2 ] = b;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
set_color( const TReal* c )
{
  this->m_Color[ 0 ] = c[ 0 ];
  this->m_Color[ 1 ] = c[ 1 ];
  this->m_Color[ 2 ] = c[ 2 ];
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
load_bounding_box( TReal* b ) const
{
  if( this->m_Points.size( ) >= 3 )
  {
    b[ 0 ] = b[ 1 ] = this->m_Points[ 0 ];
    b[ 2 ] = b[ 3 ] = this->m_Points[ 1 ];
    b[ 4 ] = b[ 5 ] = this->m_Points[ 2 ];

    for( unsigned long long i = 3; i < this->m_Points.size( ); i += 3 )
    {
      if( this->m_Points[ i ] < b[ 0 ] ) b[ 0 ] = this->m_Points[ i ];
      if( b[ 1 ] < this->m_Points[ i ] ) b[ 1 ] = this->m_Points[ i ];

      if( this->m_Points[ i + 1 ] < b[ 2 ] ) b[ 2 ] = this->m_Points[ i + 1 ];
      if( b[ 3 ] < this->m_Points[ i + 1 ] ) b[ 3 ] = this->m_Points[ i + 1 ];

      if( this->m_Points[ i + 2 ] < b[ 4 ] ) b[ 4 ] = this->m_Points[ i + 2 ];
      if( b[ 5 ] < this->m_Points[ i + 2 ] ) b[ 5 ] = this->m_Points[ i + 2 ];
    } // end for
  }
  else
  {
    b[ 0 ] = b[ 2 ] = b[ 4 ] = -1;
    b[ 1 ] = b[ 3 ] = b[ 5 ] =  1;
  } // end if
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
_local_draw( ) const
{
  /* TODO
     std::vector< TReal > m_Points;
     std::vector< TReal > m_Normals;
     std::vector< TReal > m_Textures;
     std::vector< TNat >  m_Triangles;
     std::vector< TNat >  m_Quads;
     std::vector< TNat >  m_Polygons;
     std::vector< TNat >  m_PolygonSizes;
  */

  // glBegin( GL_TRIANGLES );

  const TNat* i = this->m_Triangles.data( );
  unsigned long long N = this->m_Triangles.size( );
  for( unsigned long long t = 0; t < N; t += 9 )
  {
    TNat p1 = *( i + t );
    TNat t1 = *( i + ( t + 1 ) );
    TNat n1 = *( i + ( t + 2 ) );
    TNat p2 = *( i + ( t + 3 ) );
    TNat t2 = *( i + ( t + 4 ) );
    TNat n2 = *( i + ( t + 5 ) );
    TNat p3 = *( i + ( t + 6 ) );
    TNat t3 = *( i + ( t + 7 ) );
    TNat n3 = *( i + ( t + 8 ) );

    glBegin( GL_LINE_LOOP );

    if( n1 != 0 )
      glNormal3fv( this->m_Normals.data( ) + ( ( n1 - 1 ) * 3 ) );
    glVertex3fv( this->m_Points.data( ) + ( ( p1 - 1 ) * 3 ) );

    if( n2 != 0 )
      glNormal3fv( this->m_Normals.data( ) + ( ( n2 - 1 ) * 3 ) );
    glVertex3fv( this->m_Points.data( ) + ( ( p2 - 1 ) * 3 ) );

    if( n3 != 0 )
      glNormal3fv( this->m_Normals.data( ) + ( ( n3 - 1 ) * 3 ) );
    glVertex3fv( this->m_Points.data( ) + ( ( p3 - 1 ) * 3 ) );

    glEnd( );

  } // end for

  // glEnd( );





  /* TODO
     const TReal* p = this->m_Points.data( );
     const TReal* n = this->m_Normals.data( );
     if( this->m_DrawMode == Self::Points )
     {
     glColor3fv( this->m_Color );
     glBegin( GL_POINTS );
     {
     for( unsigned int i = 0; i < this->m_Points.size( ); i += 3 )
     glVertex3fv( p + i );
     }
     glEnd( );
     }
     else if(
     this->m_DrawMode == Self::Wireframe
     ||
     this->m_DrawMode == Self::Surface
     )
     {
     int mode
     =
     ( this->m_DrawMode == Self::Wireframe )?
     GL_LINE_LOOP:
     GL_POLYGON;
     bool has_normals
     =
     ( this->m_FacesNormals.size( ) > 0 )
     &&
     ( mode == GL_POLYGON );

     glColor3fv( this->m_Color );
     unsigned long long i = 0;
     for( const auto& sz: this->m_Sizes )
     {
     glBegin( mode );
     {
     for( unsigned long long j = 0; j < sz; ++j )
     {
     if( has_normals )
     glNormal3fv( n + this->m_FacesNormals[ ( i + j ) ] );
     glVertex3fv( p + this->m_Faces[ ( i + j ) ] );
     } // end for
     }
     glEnd( );
     i += sz;
     } // end for
     }
     else if( this->m_DrawMode == Self::SurfaceWithWireframe )
     {
     glColor3fv( this->m_Color );
     unsigned long long i = 0;
     for( const auto& sz: this->m_Sizes )
     {
     glBegin( GL_POLYGON );
     {
     for( unsigned long long j = 0; j < sz; ++j )
     glVertex3fv( p + this->m_Faces[ ( i + j ) ] );
     }
     glEnd( );
     i += sz;
     } // end for

     glColor3f(
     1 - this->m_Color[ 0 ],
     1 - this->m_Color[ 1 ],
     1 - this->m_Color[ 2 ]
     );
     i = 0;
     for( const auto& sz: this->m_Sizes )
     {
     glBegin( GL_LINE_LOOP );
     {
     for( unsigned long long j = 0; j < sz; ++j )
     glVertex3fv( p + this->m_Faces[ ( i + j ) ] );
     }
     glEnd( );
     i += sz;
     } // end for
     } // end if
  */
}

// eof - $RCSfile$
