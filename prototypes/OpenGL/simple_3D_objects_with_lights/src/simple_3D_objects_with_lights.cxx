// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <iostream>
#include "Application.h"

int main( int argc, char** argv )
{
  try
  {
    Application::init( argc, argv );
    Application::go( );
  }
  catch( const std::exception& err )
  {
    std::cerr << "Error caught: " << err.what( ) << std::endl;
    return( EXIT_FAILURE );
  } // end try
  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
