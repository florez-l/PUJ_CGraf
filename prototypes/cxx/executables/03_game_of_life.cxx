// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <PUJ/CGraf/Viewport.h>

int main( int argc, char** argv )
{
  PUJ::CGraf::FrameBuffer frame, d_frame;
  frame.load_from_netpbm( argv[ 1 ] );
  d_frame.load_from_netpbm( argv[ 2 ] );

  float total_time = 1;
  unsigned short fps = 24;
  if( argc > 3 ) total_time = std::atof( argv[ 3 ] );
  if( argc > 4 ) fps = std::atoi( argv[ 4 ] );

  unsigned long long total_frames
    = ( unsigned long long  )( float( fps ) * total_time );
  d_frame = ( d_frame - frame ) / float( total_frames - 1 );

  unsigned short pad
    = ( unsigned short )( std::ceil( std::log10( total_frames ) ) );

  for( unsigned long long frame_id = 0; frame_id < total_frames; ++frame_id )
  {
    std::stringstream filename;
    filename
      << "frame_" << std::setfill( '0' ) << std::setw( pad ) << frame_id;
    std::cout << filename.str( ) << " / " << ( total_frames - 1 ) << std::endl;

    frame.save_as_netpbm( filename.str( ) );
    frame += d_frame;
  } // end for

  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
