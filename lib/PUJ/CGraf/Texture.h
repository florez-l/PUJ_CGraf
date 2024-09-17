// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__Texture__h__
#define __PUJ__CGraf__Texture__h__

#include <PUJ/CGraf/Traits.h>




#include <cstdlib>



namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class Texture
      : public PUJ::CGraf::Object
    {
    public:
      using Self = Texture;

    public:
      Texture( )
        {
        }
      virtual ~Texture( )
        {
          if( this->m_Buffer != nullptr )
            std::free( this->m_Buffer );
        }

      void get( TReal* t, const TReal& u, const TReal& v ) const
        {
        }

      void load_from_PPM( const std::string& fname )
        {
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
          TReal max_v = 255;
          unsigned long long n = 0;
          TReal* buffer_it = nullptr;
          while( std::getline( input, line ) )
          {
            if( line[ 0 ] != '#' )
            {
              if( n == 0 )
              {
                if( line == "P1" )
                {
                  this->m_Dims[ 2 ] = 1;
                  max_v = 1;
                }
                else if( line == "P2" ) this->m_Dims[ 2 ] = 1;
                else if( line == "P3" ) this->m_Dims[ 2 ] = 3;
              }
              else if( n == 1 )
                std::istringstream( line )
                  >> this->m_Dims[ 0 ] >> this->m_Dims[ 1 ];
              else if( n == 2 )
              {
                std::istringstream real_max_str( line );
                TReal real_max;
                real_max_str >> real_max;
                max_v /= real_max;

                this->m_Size
                  = this->m_Dims[ 0 ] * this->m_Dims[ 1 ] * this->m_Dims[ 2 ];
                if( this->m_Buffer != nullptr )
                  std::free( this->m_Buffer );
                this->m_Buffer
                  = reinterpret_cast< TReal* >(
                    std::calloc( this->m_Size, sizeof( TReal ) )
                    );
                buffer_it = this->m_Buffer;
              }
              else
              {
                std::istringstream line_str( line );
                while( line_str.good( ) )
                  line_str >> *( buffer_it++ );
                buffer_it--;
              } // end if
              n++;
            } // end if
          } // end while
        }

    protected:
      unsigned short m_Dims[ 3 ]  { 0, 0, 0 };
      TReal          m_Range[ 2 ] { 0, 255 };
      TReal*         m_Buffer     { nullptr };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__Texture__h__

// eof - $RCSfile$
