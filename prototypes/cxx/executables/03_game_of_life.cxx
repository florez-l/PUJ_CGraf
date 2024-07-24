// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <PUJ/CGraf/Viewport.h>

class GameOfLife
  : public PUJ::CGraf::Viewport
{
public:
  using Self = GameOfLife;
  using Superclass = PUJ::CGraf::Viewport;

public:
  GameOfLife(
    const unsigned short& width = 100,
    const unsigned short& height = 100
    )
    : Superclass( width, height, Superclass::BINARY )
    {
    }
  GameOfLife( const Self& other )
    : Superclass( *( dynamic_cast< const Superclass* >( &other ) ) )
    {
    }
  Self& operator=( const Self& other )
    {
      this->Superclass::operator=(
        *( dynamic_cast< const Superclass* >( &other ) )
        );
      return( *this );
    }
  virtual ~GameOfLife( ) = default;

  virtual bool load_from_netpbm( const std::string& fname ) override
    {
      bool r = this->Superclass::load_from_netpbm( fname );
      if( r )
      {
        if( this->m_ColorDeep != Self::BINARY )
        {
          this->m_ColorDeep = Self::BINARY;
          this->m_Dims[ 0 ] = 100;
          this->m_Dims[ 1 ] = 100;
          this->m_Dims[ 2 ] = 1;
          this->m_Size =
            this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

          this->m_Buffer =
            reinterpret_cast< float* >(
              std::calloc( this->m_Size, sizeof( float ) )
              );
          this->random_fill( );
          throw std::logic_error( "Input image should be only binary (P1)." );
        } // end if
      } // end if
      return( r );
    }

  void evolve_into( Self& other ) const
    {
      for( short i = 0; i < this->m_Dims[ 0 ]; ++i )
      {
        for( short j = 0; j < this->m_Dims[ 1 ]; ++j )
        {
          // Get neighbors
          short a = 0;
          for( short k = -1; k <= 1; ++k )
          {
            for( short l = -1; l <= 1; ++l )
            {
              if( k != 0 || l != 0 )
              {
                short x = i + k;
                short y = j + l;
                if( this->isInside( x, y ) )
                  if( this->get( x, y ) == 1 )
                    a += 1;
              } // end if
            } // end for
          } // end for

          // Apply rules
          if( this->get( i, j ) == 1 )
            other.set( i, j, ( a == 2 || a == 3 )? 1: 0 );
          else
            other.set( i, j, ( a == 3 )? 1: 0 );
        } // end for
      } // end for
    }
};

int main( int argc, char** argv )
{
  if( argc < 4 )
  {
    std::cout
      << "Usage: " << argv[ 0 ] << " image.pbm length fps" << std::endl;
    return( EXIT_FAILURE );
  } // end if
  std::string image_fname = argv[ 1 ];
  float length;
  int fps;
  std::istringstream( argv[ 2 ] ) >> length;
  std::istringstream( argv[ 3 ] ) >> fps;

  // Create boards
  GameOfLife gol[ 2 ];
  gol[ 0 ].load_from_netpbm( image_fname );
  gol[ 1 ].clone( gol[ 0 ] );

  // Create frames
  unsigned long long total_frames = fps * length;
  int pad = int( std::ceil( std::log10( total_frames ) ) );
  for( unsigned long long frame_id; frame_id < total_frames; ++frame_id )
  {
    std::stringstream filename;
    filename
      << "frame_" << std::setfill( '0' ) << std::setw( pad ) << frame_id;
    std::cout << filename.str( ) << " / " << ( total_frames - 1 ) << std::endl;

    gol[ frame_id % 2 ].save_as_netpbm( filename.str( ).c_str( ) );
    gol[ frame_id % 2 ].evolve_into( gol[ ( frame_id + 1 ) % 2 ] );
  } // end for

  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
