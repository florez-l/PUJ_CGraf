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
    i = ( index[ 1 ] * self.m_Dims[ 0 ] ) + index[ 0 ]
    if self.m_Dims[ 2 ] == 1:
      return self.m_Buffer[ i ]
    else:
      i *= self.m_Dims[ 2 ]
      return ( self.m_Buffer[ i ], self.m_Buffer[ i + 1 ], self.m_Buffer[ i + 2 ] )
    # end if
  # end def

  '''
  '''
  def __setitem__( self, index, v ):
    if self.isInside( v ):
      i = ( index[ 1 ] * self.m_Dims[ 0 ] ) + index[ 0 ]
      if self.m_Dims[ 2 ] == 1:
        self.m_Buffer[ i ] = v
      else:
        i *= self.m_Dims[ 2 ]
        self.m_Buffer[ i ]     = v[ 0 ]
        self.m_Buffer[ i + 1 ] = v[ 1 ]
        self.m_Buffer[ i + 2 ] = v[ 2 ]
      # end if
    # end if
  # end def

  '''
  '''
  def clear( self, c ):
    if self.m_Dims[ 2 ] == 1:
      for i in range( 0, len( self.m_Buffer ), self.m_Dims[ 2 ] ):
        self.m_Buffer[ i ] = c
      # end for
    else:
      for i in range( len( self.m_Buffer ) ):
        for j in range( self.m_Dims[ 2 ] ):
          self.m_Buffer[ i ] = c[ j ]
        # end for
      # end for
    # end if
  # end def

  '''
  '''
  def draw_line( self, p0, p1, color ):
    x0, y0 = p0
    x1, y1 = p1
    dx = x1 - x0
    dy = y1 - y0
    if abs( dx ) > abs( dy ):

      if dx < 0:
        x0, y0 = p1
        x1, y1 = p0
        dx = x1 - x0
        dy = y1 - y0
      # end if

      xk = x0
      yk = y0
      dy2 = dy << 1
      pk = dy2 - dx
      dxy2 = ( dy - dx ) << 1

      while xk != x1:
        self[ ( xk, yk ) ] = color
        xk += 1
        if pk < 0:
          pk += dy2
        else:
          yk += 1
          pk += dxy2
        # end if
      # end while

    else:

      if dy < 0:
        x0, y0 = p1
        x1, y1 = p0
        dx = x1 - x0
        dy = y1 - y0
      # end if

      xk = x0
      yk = y0
      dx2 = dx << 1
      pk = dx2 - dy
      dyx2 = ( dx - dy ) << 1

      while yk != y1:
        self[ ( yk, xk ) ] = color
        yk += 1
        if pk < 0:
          pk += dx2
        else:
          xk += 1
          pk += dyx2
        # end if
      # end while

    # end if
  # end def

  '''
  '''
  def draw_circle_octants( self, cx, cy, x, y, color ):
    self[ ( cx + x, cy + y ) ] = color
    self[ ( cx - x, cy + y ) ] = color
    self[ ( cx + x, cy - y ) ] = color
    self[ ( cx - x, cy - y ) ] = color
    self[ ( cx + y, cy + x ) ] = color
    self[ ( cx - y, cy + x ) ] = color
    self[ ( cx + y, cy - x ) ] = color
    self[ ( cx - y, cy - x ) ] = color
  # end def

  '''
  '''
  def draw_circle( self, center, radius, color ):
    x = 0
    y = radius
    d = 3 - ( radius << 1 )
    self.draw_circle_octants( center[ 0 ], center[ 1 ], x, y, color )

    while x <= y:

      x += 1

      if d > 0:
        y -= 1
        d += ( ( x - y ) << 2 ) + 10
      else:
        d += ( x << 2 ) + 6
      # end if

      self.draw_circle_octants( center[ 0 ], center[ 1 ], x, y, color )

    # end while
  # end def

# end class

## eof - $RCSfile$
