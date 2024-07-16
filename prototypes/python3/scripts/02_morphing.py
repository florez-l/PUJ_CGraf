## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

total_time = 5
fps = 24

total_frames = fps * total_time
pad = int( math.ceil( math.log10( total_frames ) ) )

start = PUJ.CGraf.FrameBuffer( )
diff  = PUJ.CGraf.FrameBuffer( )
start.load_from_netpbm( sys.argv[ 1 ] )
diff.load_from_netpbm( sys.argv[ 2 ] )
diff -= start

for frame_id in range( total_frames ):
  t = frame_id / ( total_frames - 1 )

  frame = ( diff * t ) + start
  frame.cast( )
  fname = 'frame_' + str( frame_id ).rjust( pad, '0' )
  print( fname, 'total = ' + str( total_frames ) )
  frame.save_as_netpbm( fname )

# end for

## eof - $RCSfile$
