## =========================================================================
## @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
## =========================================================================

import math, sys
sys.path.append( '..' )
import PUJ.CGraf

frame = PUJ.CGraf.FrameBuffer( )
d_frame  = PUJ.CGraf.FrameBuffer( )
frame.load_from_netpbm( sys.argv[ 1 ] )
d_frame.load_from_netpbm( sys.argv[ 2 ] )

total_time = 1
fps = 24
if len( sys.argv ) > 3:
  total_time = int( sys.argv[ 3 ] )
# end if
if len( sys.argv ) > 4:
  fps = int( sys.argv[ 4 ] )
# end if

total_frames = fps * total_time
d_frame = ( d_frame - frame ) / ( total_frames - 1 )

pad = int( math.ceil( math.log10( total_frames ) ) )
for frame_id in range( total_frames ):
  filename = 'frame_' + str( frame_id ).rjust( pad, '0' )
  print( filename, ' / ' + str( total_frames - 1 ) )

  frame.save_as_netpbm( filename )
  frame += d_frame

# end for

## eof - $RCSfile$
