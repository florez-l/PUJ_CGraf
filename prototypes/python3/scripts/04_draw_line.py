## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

if len( sys.argv ) < 8:
  print( 'Usage: python3 ' + sys.argv[ 0 ] + ' i0 j0 i1 j1 r g b' )
  sys.exit( 1 )
# end if
p0 = ( int( sys.argv[ 1 ] ), int( sys.argv[ 2 ] ) )
p1 = ( int( sys.argv[ 3 ] ), int( sys.argv[ 4 ] ) )
c = ( int( sys.argv[ 5 ] ), int( sys.argv[ 6 ] ), int( sys.argv[ 7 ] ) )

# Create boards
vp = PUJ.CGraf.Viewport( ( 1024, 768 ), 'RGB' )
vp.clear( ( 0, 0, 0 ) )
vp.draw_line( p0, p1, c )
vp.save_as_netpbm( 'line.ppm' )

## eof - $RCSfile$
