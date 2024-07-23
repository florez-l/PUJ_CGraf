# =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

"""
"""
class GameOfLife( PUJ.CGraf.Viewport ):
  '''
  '''
  def __init__( self, dims = ( 100, 100 ) ):
    super( GameOfLife, self ).__init__( dims, color_deep = 'BINARY' )
  # end def

  '''
  '''
  def load_from_netpbm( self, fname ):

    super( GameOfLife, self ).load_from_netpbm( fname )

    if self.m_ColorDeep != 'BINARY':

      self.m_ColorDeep = 'BINARY'
      self.m_Dims = ( 100, 100, 1 )
      s = self.m_Dims[ 0 ] * self.m_Dims[ 1 ] * self.m_Dims[ 2 ]
      self.m_Buffer = [ 0 for i in range( s ) ]
      self.random_fill( )

      raise Exception( 'Input image should be only binary (P1).' )
    # end if
  # end def

  '''
  '''
  def evolve_into( self, other ):
    for i in range( self.m_Dims[ 0 ] ):
      for j in range( self.m_Dims[ 1 ] ):

        # Get neighbors
        alive_neighbors = 0
        for k in range( -1, 2, 1 ):
          for l in range( -1, 2, 1 ):
            if k != 0 or l != 0:
              x = i + k
              y = j + l
              if self.isInside( ( x, y ) ):
                if self[ ( x, y ) ] == 1:
                  alive_neighbors += 1
                # end if
              # end if
            # end if
          # end for
        # end for

        # Apply rules
        if self[ ( i, j ) ] == 1:
          if alive_neighbors == 2 or alive_neighbors == 3:
            other[ ( i, j ) ] = 1
          else:
            other[ ( i, j ) ] = 0
          # end if
        else:
          if alive_neighbors == 3:
            other[ ( i, j ) ] = 1
          else:
            other[ ( i, j ) ] = 0
          # end if
        # end if

      # end for
    # end for
  # end def

# end class

## ------------------------------ MAIN SCRIPT ------------------------------

# Create boards
gol = [ GameOfLife( ), GameOfLife( ) ]
gol[ 0 ].load_from_netpbm( sys.argv[ 1 ] )
gol[ 1 ].clone( gol[ 0 ] )

# Create frames
total_frames = 1000 ## fps * total_time
pad = int( math.ceil( math.log10( total_frames ) ) )
for frame_id in range( total_frames ):

  filename = 'frame_' + str( frame_id ).rjust( pad, '0' )
  print( filename + ' / ' + str( total_frames - 1 ) )

  gol[ frame_id % 2 ].save_as_netpbm( filename )
  gol[ frame_id % 2 ].evolve_into( gol[ ( frame_id + 1 ) % 2 ] )

# end for

## eof - $RCSfile$
