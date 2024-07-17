// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <PUJ/CGraf/FrameBuffer.h>

int main( int argc, char** argv )
{
  unsigned short w = 100, h = 100;
  PUJ::CGraf::FrameBuffer::ColorDeep depth = PUJ::CGraf::FrameBuffer::RGB;
  std::string fname = "frame.ppm";

  if( argc > 1 ) w = std::atoi( argv[ 1 ] );
  if( argc > 2 ) h = std::atoi( argv[ 2 ] );
  if( argc > 3 )
  {
    std::string d = argv[ 3 ];
    std::transform( d.begin( ), d.end( ), d.begin( ), ::toupper );

    if     ( d == "BINARY" ) depth = PUJ::CGraf::FrameBuffer::BINARY;
    else if( d == "GRAY" )   depth = PUJ::CGraf::FrameBuffer::GRAY;
    else                     depth = PUJ::CGraf::FrameBuffer::RGB;
  } // end if
  if( argc > 4 ) fname = argv[ 4 ];

  PUJ::CGraf::FrameBuffer frame( w, h, depth );
  frame.save_as_netpbm( fname );

  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
