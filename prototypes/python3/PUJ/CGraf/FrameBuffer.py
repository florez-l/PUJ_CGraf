## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import os, random

"""
"""
class FrameBuffer:

  '''
  '''
  def __init__( self, dims = ( 256, 256 ), color_deep = 'RGB' ):
    deep = color_deep.upper( )
    if deep in [ 'BINARY', 'GRAY' ]:
      self.m_ColorDeep = deep
      self.m_Dims = ( dims[ 0 ], dims[ 1 ], 1 )
    else:
      self.m_ColorDeep = 'RGB'
      self.m_Dims = ( dims[ 0 ], dims[ 1 ], 3 )
    # end if
    s = self.m_Dims[ 0 ] * self.m_Dims[ 1 ] * self.m_Dims[ 2 ]
    self.m_Buffer = [ 0 for i in range( s ) ]
    self.random_fill( )
  # end def

  '''
  '''
  def random_fill( self ):
    max_v = 255
    if self.m_ColorDeep == 'BINARY':
      max_v = 1
    # end if
    for i in range( len( self.m_Buffer ) ):
      self.m_Buffer[ i ] = random.randint( 0, max_v )
    # end for
  # end def

  '''
  '''
  def __add__( self, other ):
    r = FrameBuffer( dims = self.m_Dims, color_deep = self.m_ColorDeep )
    r.m_Buffer = [ a + b for a, b in zip( self.m_Buffer, other.m_Buffer ) ]
    return r
  # end def

  '''
  '''
  def __sub__( self, other ):
    r = FrameBuffer( dims = self.m_Dims, color_deep = self.m_ColorDeep )
    r.m_Buffer = [ a - b for a, b in zip( self.m_Buffer, other.m_Buffer ) ]
    return r
  # end def

  '''
  '''
  def __mul__( self, coeff ):
    r = FrameBuffer( dims = self.m_Dims, color_deep = self.m_ColorDeep )
    r.m_Buffer = [ a * coeff for a in self.m_Buffer ]
    return r
  # end def

  '''
  '''
  def cast( self ):
    for i in range( len( self.m_Buffer ) ):
      self.m_Buffer[ i ] = int( self.m_Buffer[ i ] )
    # end for
  # end def

  '''
  '''
  def save_as_netpbm( self, fname ):

    # Create file contents
    s = ''
    if self.m_ColorDeep == 'BINARY':
      s += 'P1\n'
      s += str( self.m_Dims[ 0 ] ) + ' ' + str( self.m_Dims[ 1 ] ) + '\n'
      s += '1\n'
    elif self.m_ColorDeep == 'GRAY':
      s += 'P2\n'
      s += str( self.m_Dims[ 0 ] ) + ' ' + str( self.m_Dims[ 1 ] ) + '\n'
      s += '255\n'
    else:
      s += 'P3\n'
      s += str( self.m_Dims[ 0 ] ) + ' ' + str( self.m_Dims[ 1 ] ) + '\n'
      s += '255\n'
    # end if

    nl = self.m_Dims[ 1 ] * self.m_Dims[ 2 ]
    for i in range( len( self.m_Buffer ) ):
      end_c = ' '
      if i % nl == 0:
        end_c = '\n'
      # end if
      s += str( self.m_Buffer[ i ] ) + end_c
    # end for

    # Build a coherent filename
    dir_name = os.path.dirname( fname )
    base_name = os.path.splitext( os.path.basename( fname ) )[ 0 ]
    ext_name = ''
    if self.m_ColorDeep == 'BINARY':
      ext_name = '.pbm'
    elif self.m_ColorDeep == 'GRAY':
      ext_name = '.pgm'
    else:
      ext_name = '.ppm'
    # end if
    real_fname = os.path.join( dir_name, base_name + ext_name )

    # Real save
    real_ifs = open( real_fname, 'w' )
    real_ifs.write( s )
    real_ifs.close( )
    
  # end def

  '''
  '''
  def load_from_netpbm( self, fname ):
    pass
  # end def

# end class

## --------- SOME TESTING ---------
if __name__ == "__main__":
  img = FrameBuffer( )
  img.save_as_netpbm( 'a_test.png' )
# end if

## eof - $RCSfile$
