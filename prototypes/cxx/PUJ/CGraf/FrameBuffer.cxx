// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/FrameBuffer.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
FrameBuffer(
  const unsigned short& width,
  const unsigned short& height,
  const ColorDeep& color_deep
  )
{
  this->m_ColorDeep = color_deep;
  this->m_Dims[ 0 ] = width;
  this->m_Dims[ 1 ] = height;

  if( this->m_ColorDeep == Self::BINARY || this->m_ColorDeep == Self::GRAY )
    this->m_Dims[ 2 ] = 1;
  else
    this->m_Dims[ 2 ] = 3;
  this->m_Size = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  this->m_Buffer =
    reinterpret_cast< float* >( std::calloc( this->m_Size, sizeof( float ) ) );
  this->random_fill( );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
FrameBuffer( const Self& other )
{
  this->m_ColorDeep = other.m_ColorDeep;
  this->m_Dims[ 0 ] = other.m_Dims[ 0 ];
  this->m_Dims[ 1 ] = other.m_Dims[ 1 ];
  this->m_Dims[ 2 ] = other.m_Dims[ 2 ];
  this->m_Size = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  this->m_Buffer =
    reinterpret_cast< float* >( std::calloc( this->m_Size, sizeof( float ) ) );
  std::memcpy(
    this->m_Buffer, other.m_Buffer, this->m_Size * sizeof( float )
    );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator=( const Self& other )
{
  this->m_ColorDeep = other.m_ColorDeep;
  this->m_Dims[ 0 ] = other.m_Dims[ 0 ];
  this->m_Dims[ 1 ] = other.m_Dims[ 1 ];
  this->m_Dims[ 2 ] = other.m_Dims[ 2 ];
  this->m_Size = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  if( this->m_Buffer != nullptr )
    std::free( this->m_Buffer );
  this->m_Buffer =
    reinterpret_cast< float* >( std::calloc( this->m_Size, sizeof( float ) ) );
  std::memcpy(
    this->m_Buffer, other.m_Buffer, this->m_Size * sizeof( float )
    );

  return( *this );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
~FrameBuffer( )
{
  if( this->m_Buffer != nullptr )
    std::free( this->m_Buffer );
}

// -------------------------------------------------------------------------
void PUJ::CGraf::FrameBuffer::
clone( const Self& other )
{
  *this = other;
}

// -------------------------------------------------------------------------
void PUJ::CGraf::FrameBuffer::
random_fill( )
{
  std::random_device dev;
  std::mt19937 eng( dev( ) );
  std::uniform_int_distribution< unsigned char >
    dist( 0, ( this->m_ColorDeep == Self::BINARY )? 1: 255 );
  std::generate(
    this->m_Buffer, this->m_Buffer + this->m_Size,
    [&]( ) -> float
    {
      return( float( dist( eng ) ) );
    }
    );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self PUJ::CGraf::FrameBuffer::
operator+( const Self& other ) const
{
  Self res( *this );
  res += other;
  return( res );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator+=( const Self& other )
{
  std::transform(
    this->m_Buffer,
    this->m_Buffer
    +
    ( ( this->m_Size < other.m_Size )? this->m_Size: other.m_Size ),
    other.m_Buffer,
    this->m_Buffer,
    []( const float& a, const float& b ) -> float
    {
      return( a + b );
    }
    );
  return( *this );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self PUJ::CGraf::FrameBuffer::
operator-( const Self& other ) const
{
  Self res( *this );
  res -= other;
  return( res );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator-=( const Self& other )
{
  std::transform(
    this->m_Buffer,
    this->m_Buffer
    +
    ( ( this->m_Size < other.m_Size )? this->m_Size: other.m_Size ),
    other.m_Buffer,
    this->m_Buffer,
    []( const float& a, const float& b ) -> float
    {
      return( a - b );
    }
    );
  return( *this );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self PUJ::CGraf::FrameBuffer::
operator*( const float& coeff ) const
{
  Self res( *this );
  res *= coeff;
  return( res );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator*=( const float& coeff )
{
  std::transform(
    this->m_Buffer, this->m_Buffer + this->m_Size, this->m_Buffer,
    [&]( const float& a ) -> float
    {
      return( a * coeff );
    }
    );
  return( *this );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self PUJ::CGraf::FrameBuffer::
operator/( const float& coeff ) const
{
  Self res( *this );
  res /= coeff;
  return( res );
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator/=( const float& coeff )
{
  std::transform(
    this->m_Buffer, this->m_Buffer + this->m_Size, this->m_Buffer,
    [&]( const float& a ) -> float
    {
      return( a / coeff );
    }
    );
  return( *this );
}

// -------------------------------------------------------------------------
bool PUJ::CGraf::FrameBuffer::
save_as_netpbm( const std::string& fname )
{
  std::stringstream s;

  // Value range
  float max_v = ( this->m_ColorDeep == Self::BINARY )? 1: 255;

  // Create file contents
  if( this->m_ColorDeep == Self::BINARY )
    s << "P1" << std::endl
      << this->m_Dims[ 0 ] << " " << this->m_Dims[ 1 ] << std::endl
      << "1" << std::endl;
  else if( this->m_ColorDeep == Self::GRAY )
    s << "P2" << std::endl
      << this->m_Dims[ 0 ] << " " << this->m_Dims[ 1 ] << std::endl
      << "255" << std::endl;
  else
    s << "P3" << std::endl
      << this->m_Dims[ 0 ] << " " << this->m_Dims[ 1 ] << std::endl
      << "255" << std::endl;

  unsigned long long nl = this->m_Dims[ 1 ] * this->m_Dims[ 2 ];
  for( unsigned long long i = 0; i < this->m_Size; ++i )
  {
    float v = this->m_Buffer[ i ];
    if( v < 0 )     v = 0;
    if( v > max_v ) v = max_v;

    s << int( v );
    if( i % nl == 0 )
      s << std::endl;
    else
      s << " ";
  } // end for

  // Build a coherent filename
  auto real_fname = std::filesystem::path( fname ).stem( );
  std::string ext_name = "";
  if( this->m_ColorDeep == Self::BINARY )    ext_name = ".pbm";
  else if( this->m_ColorDeep == Self::GRAY ) ext_name = ".pgm";
  else                                       ext_name = ".ppm";
  real_fname.replace_extension( std::filesystem::path( ext_name ) );

  // Real save
  std::ofstream real_ofs( real_fname );
  real_ofs.write( s.str( ).c_str( ), s.str( ).size( ) );
  real_ofs.close( );

  return( true );
}

// -------------------------------------------------------------------------
bool PUJ::CGraf::FrameBuffer::
load_from_netpbm( const std::string& fname )
{
  // Load buffer
  std::ifstream ifs( fname.c_str( ) );
  if( !ifs )
    return( false );
  ifs.seekg( 0, std::ios::end );
  std::size_t size = ifs.tellg( );
  ifs.seekg( 0, std::ios::beg );
  std::string buffer( size, 0 );
  ifs.read( &buffer[ 0 ], size );
  ifs.close( );
  std::istringstream input( buffer );

  // Read line by line
  std::string line;
  float max_v = 255;
  unsigned long long n = 0;
  float* buffer_it = nullptr;
  while( std::getline( input, line ) )
  {
    if( line[ 0 ] != '#' )
    {
      if( n == 0 )
      {
        if( line == "P1" )
        {
          this->m_ColorDeep = Self::BINARY;
          this->m_Dims[ 2 ] = 1;
          max_v = 1;
        }
        else if( line == "P2" )
        {
          this->m_ColorDeep = Self::GRAY;
          this->m_Dims[ 2 ] = 1;
        }
        else if( line == "P3" )
        {
          this->m_ColorDeep = Self::RGB;
          this->m_Dims[ 2 ] = 3;
        } // end if
      }
      else if( n == 1 )
      {
        std::istringstream dims( line );
        dims >> this->m_Dims[ 0 ] >> this->m_Dims[ 1 ];
      }
      else if( n == 2 )
      {
        std::istringstream real_max_str( line );
        float real_max;
        real_max_str >> real_max;
        max_v /= real_max;

        this->m_Size
          = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];
        if( this->m_Buffer != nullptr )
          std::free( this->m_Buffer );
        this->m_Buffer
          = reinterpret_cast< float* >(
            std::calloc( this->m_Size, sizeof( float ) )
            );
        buffer_it = this->m_Buffer;
      }
      else
      {
        std::istringstream line_str( line );
        while( line_str.good( ) )
          line_str >> *( buffer_it++ );
        buffer_it--;
      } // end if
      n++;
    } // end if
  } // end while

  return( true );
}


// eof - $RCSfile$
