// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Texture.h>

#include <cstdlib>
#include <fstream>
#include <sstream>

// -------------------------------------------------------------------------
PUJ::CGraf::Texture::
Texture( )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::Texture::
~Texture( )
{
  if( this->m_Buffer != nullptr )
    std::free( this->m_Buffer );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Texture::
get( TReal* t, const TReal& u, const TReal& v ) const
{
  unsigned long long i
    =
    ( unsigned long long )( TReal( this->m_Dims[ 0 ] ) * u );
  unsigned long long j
    =
    ( unsigned long long )( TReal( this->m_Dims[ 1 ] ) * v );

  const TReal* b
    =
    this->m_Buffer
    +
    ( ( ( i * this->m_Dims[ 1 ] ) + j ) * this->m_Dims[ 2 ] );
  for( unsigned long long d = 0; d < this->m_Dims[ 2 ]; ++d )
    t[ d ] = b[ d ];
}

// -------------------------------------------------------------------------
void PUJ::CGraf::Texture::
load_from_PPM( const std::string& fname )
{
  // Load data into a buffer
  std::ifstream fs(
    fname.c_str( ), std::ios::in | std::ios::binary | std::ios::ate
    );
  std::size_t fl = fs.tellg( );
  if( fl == 0 )
  {
    std::stringstream err;
    err
      << "Unable to read an OBJ model from \""
      << fname << "\""
      << std::endl;
    throw std::invalid_argument( err.str( ) );
  } // end if
  fs.seekg( 0, std::ios::beg );
  std::string str( fl, '\0' );
  if( fs.is_open( ) )
    fs.read( &str[ 0 ], fl );
  fs.close( );
  std::istringstream ds( str );

  // Read data
  unsigned long long size = 0;
  std::string line;
  TReal max_v = 255;
  unsigned long long n = 0;
  TReal* buffer_it = nullptr;
  while( std::getline( ds, line ) )
  {
    if( line[ 0 ] != '#' )
    {
      if( n == 0 )
      {
        if( line == "P1" )
        {
          this->m_Dims[ 2 ] = 1;
          max_v = 1;
        }
        else if( line == "P2" ) this->m_Dims[ 2 ] = 1;
        else if( line == "P3" ) this->m_Dims[ 2 ] = 3;
      }
      else if( n == 1 )
        std::istringstream( line )
          >> this->m_Dims[ 0 ] >> this->m_Dims[ 1 ];
      else if( n == 2 )
      {
        if( max_v != 1 )
        {
          std::istringstream max_str( line );
          max_str >> max_v;
        } // end if

        size
          = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];
        if( this->m_Buffer != nullptr )
          std::free( this->m_Buffer );
        this->m_Buffer
          = reinterpret_cast< TReal* >(
            std::calloc( size, sizeof( TReal ) )
            );
        buffer_it = this->m_Buffer;
      }
      else
      {
        std::istringstream line_str( line );
        while( line_str.good( ) )
        {
          line_str >> *buffer_it;
          *( buffer_it++ ) /= max_v;
        } // end while
        buffer_it--;
      } // end if
      n++;
    } // end if
  } // end while
}

// eof - $RCSfile$
