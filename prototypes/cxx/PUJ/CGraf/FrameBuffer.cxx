// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/FrameBuffer.h>

#include <cstdlib>

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
  else:
    this->m_Dims[ 2 ] = 3;
  unsigned long long s =
    this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  this->m_Buffer = std::calloc( s, sizeof( unsigned char ) );
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
  unsigned long long s =
    this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  this->m_Buffer = std::calloc( s, sizeof( unsigned char ) );
  std::memcpy( this->m_Buffer, other.m_Buffer, s * sizeof( unsigned char ) );
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
  unsigned long long s =
    this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];

  if( this->m_Buffer != nullptr )
    std::free( this->m_Buffer );
  this->m_Buffer = std::calloc( s, sizeof( unsigned char ) );
  std::memcpy( this->m_Buffer, other.m_Buffer, s * sizeof( unsigned char ) );

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
random_fill( )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator+( const Self& other ) const
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator+=( const Self& other )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator-( const Self& other ) const
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator-=( const Self& other )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator*( const Self& other ) const
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator*=( const Self& other )
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator/( const Self& other ) const
{
}

// -------------------------------------------------------------------------
PUJ::CGraf::FrameBuffer::
Self& PUJ::CGraf::FrameBuffer::
operator/=( const Self& other )
{
}

// -------------------------------------------------------------------------
bool PUJ::CGraf::FrameBuffer::
save_as_netpbm( const std::string& fname )
{
}

// -------------------------------------------------------------------------
bool PUJ::CGraf::FrameBuffer::
load_from_netpbm( const std::string& fname )
{
}

// eof - $RCSfile$





## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import os, random

"""
"""
class FrameBuffer:

  '''
  '''
  def __init__( self, dims = ( 512, 512 ), color_deep = 'RGB' ):
  # end def

  '''
  '''
  def random_fill( self ):
    max_v = 255
    if this->m_ColorDeep == 'BINARY':
      max_v = 1
    # end if
    for i in range( len( this->m_Buffer ) ):
      this->m_Buffer[ i ] = random.randint( 0, max_v )
    # end for
  # end def

  '''
  '''
  def __add__( self, other ):
    r = FrameBuffer( dims = this->m_Dims, color_deep = this->m_ColorDeep )
    r.m_Buffer = [ a + b for a, b in zip( this->m_Buffer, other.m_Buffer ) ]
    return r
  # end def

  '''
  '''
  def __iadd__( self, other ):
    for i in range( len( this->m_Buffer ) ):
      this->m_Buffer[ i ] += other.m_Buffer[ i ]
    # end for
    return self
  # end def

  '''
  '''
  def __sub__( self, other ):
    r = FrameBuffer( dims = this->m_Dims, color_deep = this->m_ColorDeep )
    r.m_Buffer = [ a - b for a, b in zip( this->m_Buffer, other.m_Buffer ) ]
    return r
  # end def

  '''
  '''
  def __isub__( self, other ):
    for i in range( len( this->m_Buffer ) ):
      this->m_Buffer[ i ] -= other.m_Buffer[ i ]
    # end for
    return self
  # end def

  '''
  '''
  def __mul__( self, coeff ):
    r = FrameBuffer( dims = this->m_Dims, color_deep = this->m_ColorDeep )
    r.m_Buffer = [ a * coeff for a in this->m_Buffer ]
    return r
  # end def

  '''
  '''
  def __imul__( self, coeff ):
    for i in range( len( this->m_Buffer ) ):
      this->m_Buffer[ i ] *= coeff
    # end for
    return self
  # end def

  '''
  '''
  def __truediv__( self, coeff ):
    r = FrameBuffer( dims = this->m_Dims, color_deep = this->m_ColorDeep )
    r.m_Buffer = [ a / coeff for a in this->m_Buffer ]
    return r
  # end def

  '''
  '''
  def __itruediv__( self, coeff ):
    for i in range( len( this->m_Buffer ) ):
      this->m_Buffer[ i ] /= coeff
    # end for
    return self
  # end def

  '''
  '''
  def save_as_netpbm( self, fname ):

    # Value range
    max_v = 255
    if this->m_ColorDeep == 'BINARY':
      max_v = 1
    # end if

    # Create file contents
    s = ''
    if this->m_ColorDeep == 'BINARY':
      s += 'P1\n'
      s += str( this->m_Dims[ 0 ] ) + ' ' + str( this->m_Dims[ 1 ] ) + '\n'
      s += '1\n'
    elif this->m_ColorDeep == 'GRAY':
      s += 'P2\n'
      s += str( this->m_Dims[ 0 ] ) + ' ' + str( this->m_Dims[ 1 ] ) + '\n'
      s += '255\n'
    else:
      s += 'P3\n'
      s += str( this->m_Dims[ 0 ] ) + ' ' + str( this->m_Dims[ 1 ] ) + '\n'
      s += '255\n'
    # end if

    nl = this->m_Dims[ 1 ] * this->m_Dims[ 2 ]
    for i in range( len( this->m_Buffer ) ):
      end_c = ' '
      if i % nl == 0:
        end_c = '\n'
      # end if

      v = this->m_Buffer[ i ]
      if v < 0:
        v = 0
      # end if
      if v > max_v:
        v = max_v
      # end if

      s += str( int( v ) ) + end_c
    # end for

    # Build a coherent filename
    dir_name = os.path.dirname( fname )
    base_name = os.path.splitext( os.path.basename( fname ) )[ 0 ]
    ext_name = ''
    if this->m_ColorDeep == 'BINARY':
      ext_name = '.pbm'
    elif this->m_ColorDeep == 'GRAY':
      ext_name = '.pgm'
    else:
      ext_name = '.ppm'
    # end if
    real_fname = os.path.join( dir_name, base_name + ext_name )

    # Real save
    real_ofs = open( real_fname, 'w' )
    real_ofs.write( s )
    real_ofs.close( )

  # end def

  '''
  '''
  def load_from_netpbm( self, fname ):

    # Load file
    real_ifs = open( fname, 'r' )
    lines = real_ifs.readlines( )
    real_ifs.close( )
    real_lines = []
    for line in lines:
      if line[ 0 ] != '#' and line.strip( ) != '':
        real_lines += [ line.strip( ) ]
      # end if
    # end for

    mn = real_lines[ 0 ]
    dims = [ int( v ) for v in real_lines[ 1 ].split( ) ]
    max_v = 255
    if mn == 'P1':
      this->m_ColorDeep = 'BINARY'
      this->m_Dims = ( dims[ 0 ], dims[ 1 ], 1 )
      max_v = 1
    elif mn == 'P2':
      this->m_ColorDeep = 'GRAY'
      this->m_Dims = ( dims[ 0 ], dims[ 1 ], 1 )
    else:
      this->m_ColorDeep = 'RGB'
      this->m_Dims = ( dims[ 0 ], dims[ 1 ], 3 )
    # end if
    max_v /= float( real_lines[ 2 ] )

    this->m_Buffer = []
    for line in lines[ 3 : ]:
      for v in line.split( ):
        this->m_Buffer += [ int( float( v ) * max_v ) ]
      # end for
    # end for
  # end def

# end class

## --------- SOME TESTING ---------
if __name__ == "__main__":
  img = FrameBuffer( )
  img.save_as_netpbm( 'a_test.png' )
# end if

## eof - $RCSfile$
