// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Mesh.h>

#include <fstream>
#include <sstream>

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
load_from_OBJ( const std::string& fname )
{
  // Clean previous data
  this->m_Points.clear( );
  this->m_Indices.clear( );
  this->m_Sizes.clear( );

  // Load data into a buffer
  std::ifstream fs(
    fname.c_str( ), std::ios::in | std::ios::binary | std::ios::ate
    );
  std::size_t fl = fs.tellg( );
  if( fl == 0 )
  {
    // ERROR
  } // end if
  fs.seekg( 0, std::ios::beg );
  std::string str( fl, '\0' );
  if( fs.is_open( ) )
    fs.read( &str[ 0 ], fl );
  fs.close( );
  std::istringstream ds( str );

  // Read data
  std::string line;
  while( std::getline( ds, line ) )
  {
    std::size_t b = str.find_first_not_of( " \t" );

    if( line.data( )[ b ] != '#' && line.data( )[ b ] != '\0' )
    {
      std::istringstream ls( line.data( ) + b );
      std::string cmd;
      ls >> cmd;

      if( cmd == "v" )
      {
        TReal x, y, z;
        ls >> x >> y >> z;
        this->m_Points.push_back( x );
        this->m_Points.push_back( y );
        this->m_Points.push_back( z );
      }
      else if( cmd == "f" )
      {
        TNat i;
        unsigned long long s = this->m_Indices.size( );
        while( ls >> i )
          this->m_Indices.push_back( i - 1 );
        this->m_Sizes.push_back( this->m_Indices.size( ) - s );
      } // end if
    } // end if
  } // end while

  this->m_Points.shrink_to_fit( );
  this->m_Indices.shrink_to_fit( );
  this->m_Sizes.shrink_to_fit( );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
_local_draw( ) const
{
  if( this->m_DrawMode == Self::Points )
  {
    glColor3fv( this->m_Color );
    glBegin( GL_POINTS );
    {
      for( unsigned int i = 0; i < this->m_Points.size( ); i += 3 )
        glVertex3fv( this->m_Points.data( ) + i );
    }
    glEnd( );
  }
  else if( this->m_DrawMode == Self::Wireframe )
  {
    glColor3fv( this->m_Color );
    unsigned long long i = 0;
    for( const auto& sz: this->m_Sizes )
    {
      glBegin( GL_LINE_LOOP );
      {
        for( unsigned long long j = 0; j < sz; ++j )
          glVertex3fv( this->m_Points.data( ) + this->m_Indices[ i + j ] );
      }
      glEnd( );
      i += sz;
    } // end for
  }
  else if( this->m_DrawMode == Self::Surface )
  {
    glColor3fv( this->m_Color );
    unsigned long long i = 0;
    for( const auto& sz: this->m_Sizes )
    {
      glBegin( GL_POLYGON );
      {
        for( unsigned long long j = 0; j < sz; ++j )
          glVertex3fv( this->m_Points.data( ) + this->m_Indices[ i + j ] );
      }
      glEnd( );
      i += sz;
    } // end for
  }
  else if( this->m_DrawMode == Self::SurfaceWithWireframe )
  {
  } // end if
}

// eof - $RCSfile$
