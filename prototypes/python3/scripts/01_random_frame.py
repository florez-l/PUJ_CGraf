## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

# -- Input arguments
size = ( 100, 100 )
color_depth = 'rgb'
fname = 'frame.ppm'
if len( sys.argv ) > 2:
  size = ( int( sys.argv[ 1 ] ), int( sys.argv[ 2 ] ) )
# end if
if len( sys.argv ) > 3:
  color_depth = sys.argv[ 3 ]
# end if
if len( sys.argv ) > 4:
  fname = sys.argv[ 4 ]
# end if

# -- Create and save a random frame
frame = PUJ.CGraf.FrameBuffer( size, color_depth )
frame.save_as_netpbm( fname )

## eof - $RCSfile$
