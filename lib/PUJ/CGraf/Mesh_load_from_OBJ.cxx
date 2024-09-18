// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include <PUJ/CGraf/Mesh.h>

#include <fstream>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <PUJ/CGraf/Texture.h>

namespace PUJ
{
  namespace CGraf
  {
    // ---------------------------------------------------------------------
    template< class _TN >
    void _Mesh_load_OBJ_face(
      const std::vector< std::string >& pieces, std::vector< _TN >& topo
      )
    {
      boost::char_separator< char > s( "/" );
      for( const std::string& p: pieces )
      {
        boost::tokenizer< boost::char_separator< char > > tokens( p, s );
        auto i = tokens.begin( );
        unsigned short ntoks = std::distance( i, tokens.end( ) );

        if( ntoks == 1 )
        {
          topo.push_back( 0 );
          std::istringstream( *i ) >> topo.back( );
          topo.push_back( 0 );
          topo.push_back( 0 );
        }
        else if( ntoks == 3 )
        {
          topo.push_back( 0 );
          std::istringstream( *( i++ ) ) >> topo.back( );
          topo.push_back( 0 );
          std::istringstream( *( i++ ) ) >> topo.back( );
          topo.push_back( 0 );
          std::istringstream( *( i++ ) ) >> topo.back( );
        }
        else if( ntoks == 2 )
        {
          topo.push_back( 0 );
          std::istringstream( *( i++ ) ) >> topo.back( );

          auto n = std::count( p.begin( ), p.end( ), '/' );
          if( n == 1 )
          {
            topo.push_back( 0 );
            std::istringstream( *( i++ ) ) >> topo.back( );
            topo.push_back( 0 );
          }
          else if( n == 2 )
          {
            topo.push_back( 0 );
            topo.push_back( 0 );
            std::istringstream( *( i++ ) ) >> topo.back( );
          } // end if
        } // end if
      } // end for
    }
  } // end namespace
} // end namespace

// -------------------------------------------------------------------------
void PUJ::CGraf::Mesh::
load_from_OBJ( const std::string& fname )
{
  // Clean previous data
  this->m_Points.clear( );
  this->m_Normals.clear( );
  this->m_Textures.clear( );
  this->m_Triangles.clear( );
  this->m_Quads.clear( );
  this->m_Polygons.clear( );
  this->m_PolygonSizes.clear( );

  // Load data into a buffer
  std::ifstream fs(
    fname.c_str( ), std::ios::in | std::ios::binary | std::ios::ate
    );
  std::size_t fl = fs.tellg( );
  if( fl == 0 )
  {
    std::stringstream err;
    err
      << "Unable to read an OBJ model from \""
      << fname << "\""
      << std::endl;
    throw std::invalid_argument( err.str( ) );
  } // end if
  fs.seekg( 0, std::ios::beg );
  std::string str( fl, '\0' );
  if( fs.is_open( ) )
    fs.read( &str[ 0 ], fl );
  fs.close( );
  std::istringstream ds( str );

  // Read data
  std::string line;
  while( std::getline( ds, line ) )
  {
    std::size_t b = str.find_first_not_of( " \t" );
    if( line.data( )[ b ] != '#' && line.data( )[ b ] != '\0' )
    {
      std::istringstream ls( line.data( ) + b );
      std::string cmd;
      ls >> cmd;

      if( cmd == "v" )
      {
        TReal x, y, z;
        ls >> x >> y >> z;
        this->m_Points.push_back( x );
        this->m_Points.push_back( y );
        this->m_Points.push_back( z );
      }
      else if( cmd == "vn" )
      {
        TReal x, y, z;
        ls >> x >> y >> z;
        this->m_Normals.push_back( x );
        this->m_Normals.push_back( y );
        this->m_Normals.push_back( z );
      }
      else if( cmd == "vt" )
      {
        TReal u, v;
        ls >> u >> v;
        this->m_Textures.push_back( u );
        this->m_Textures.push_back( v );
      }
      else if( cmd == "f" )
      {
        std::vector< std::string > tokens;
        std::string tok;
        while( ls >> tok )
          tokens.push_back( tok );

        if( tokens.size( ) == 3 )
          PUJ::CGraf::_Mesh_load_OBJ_face( tokens, this->m_Triangles );
        else if( tokens.size( ) == 4 )
          PUJ::CGraf::_Mesh_load_OBJ_face( tokens, this->m_Quads );
        else if( tokens.size( ) > 4 )
          PUJ::CGraf::_Mesh_load_OBJ_face( tokens, this->m_Polygons );
      }
      else if( cmd == "o" )
      {
      }
      else if( cmd == "g" )
      {
      }
      else if( cmd == "s" )
      {
      }
      else if( cmd == "mtllib" )
      {
      }
      else if( cmd == "usemtl" )
      {
      } // end if
    } // end if
  } // end while

  this->m_Points.shrink_to_fit( );
  this->m_Normals.shrink_to_fit( );
  this->m_Textures.shrink_to_fit( );
  this->m_Triangles.shrink_to_fit( );
  this->m_Quads.shrink_to_fit( );
  this->m_Polygons.shrink_to_fit( );
}

// eof - $RCSfile$
