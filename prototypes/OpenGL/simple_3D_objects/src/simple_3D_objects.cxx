// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <fstream>
#include <iostream>
#include <sstream>

#include <string>

#include <vector>

int main( int argc, char** argv )
{

  using TReal = float;
  using TNat = unsigned short;
  
  std::vector< TReal > points;
  std::vector< TNat > indices;
  std::vector< TNat > sizes;

  std::ifstream fs( argv[ 1 ], std::ios::in | std::ios::binary | std::ios::ate );
  std::size_t fl = fs.tellg( );
  if( fl == 0 )
  {
    // error handling here
  }
  fs.seekg( 0, std::ios::beg );
  std::string str( fl, '\0' );
  if( fs.is_open( ) )
    fs.read( &str[ 0 ], fl );
  fs.close( );
  std::istringstream ds( str );

  std::string line;
  while( std::getline( ds, line ) )
  {
    std::size_t b = str.find_first_not_of( " \t" );

    if( line.data( )[ b ] != '#' && line.data( )[ b ] != '\0' )
    {
      std::cout << line << std::endl;
    } // end if

  } // end while


  return( EXIT_SUCCESS );
}

// eof - $RCSfile$
