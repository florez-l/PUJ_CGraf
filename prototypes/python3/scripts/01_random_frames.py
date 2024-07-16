## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

size = ( 100, 100 )
color_depth = 'rgb'
total_time = 15
fps = 24

total_frames = fps * total_time
pad = int( math.ceil( math.log10( total_frames ) ) )

start = PUJ.CGraf.FrameBuffer( size, color_depth )
diff  = PUJ.CGraf.FrameBuffer( size, color_depth ) - start

for frame_id in range( total_frames ):
  t = frame_id / ( total_frames - 1 )

  frame = ( diff * t ) + start
  frame.cast( )
  fname = 'frame_' + str( frame_id ).rjust( pad, '0' )
  print( fname, 'total = ' + str( total_frames ) )
  frame.save_as_netpbm( fname )

# end for

## eof - $RCSfile$
