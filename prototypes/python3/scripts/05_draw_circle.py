## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

if len( sys.argv ) < 7:
  print( 'Usage: python3 ' + sys.argv[ 0 ] + ' center_x center_y radius r g b' )
  sys.exit( 1 )
# end if
center = ( int( sys.argv[ 1 ] ), int( sys.argv[ 2 ] ) )
radius = int( sys.argv[ 3 ] )
color  = ( int( sys.argv[ 4 ] ), int( sys.argv[ 5 ] ), int( sys.argv[ 6 ] ) )

# Create boards
vp = PUJ.CGraf.Viewport( ( 1024, 768 ), 'RGB' )
vp.clear( ( 0, 0, 0 ) )
vp.draw_circle( center, radius, color )
vp.save_as_netpbm( 'circle.ppm' )

## eof - $RCSfile$
