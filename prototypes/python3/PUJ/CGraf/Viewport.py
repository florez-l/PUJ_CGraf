## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import os, random
from .FrameBuffer import FrameBuffer as PUJ_CGraf_FrameBuffer

"""
"""
class Viewport( PUJ_CGraf_FrameBuffer ):

  '''
  '''
  def __init__( self, dims = ( 512, 512 ), color_deep = 'RGB' ):
      super( Viewport, self ).__init__( dims, color_deep )
  # end def

  '''
  '''
  def isInside( self, index ):
      return \
        index[ 0 ] >= 0 and \
        index[ 1 ] >= 0 and \
        index[ 0 ] < self.m_Dims[ 0 ] and \
        index[ 1 ] < self.m_Dims[ 1 ]
  # end def

  '''
  '''
  def __getitem__( self, index ):
    i = ( ( index[ 1 ] * self.m_Dims[ 0 ] ) + index[ 0 ] ) * self.m_Dims[ 2 ]
    return self.m_Buffer[ i ]
  # end def

  '''
  '''
  def __setitem__( self, index, v ):
    i = ( ( index[ 1 ] * self.m_Dims[ 0 ] ) + index[ 0 ] ) * self.m_Dims[ 2 ]
    self.m_Buffer[ i ] = v
  # end def

# end class

## eof - $RCSfile$
