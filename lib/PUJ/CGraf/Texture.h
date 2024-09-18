// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__Texture__h__
#define __PUJ__CGraf__Texture__h__

#include <PUJ/CGraf/Traits.h>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class Texture
    {
    public:
      using Self = Texture;

    public:
      Texture( );
      virtual ~Texture( );

      void get( TReal* t, const TReal& u, const TReal& v ) const;
      void load_from_PPM( const std::string& fname );

    protected:
      unsigned short m_Dims[ 3 ]  { 0, 0, 0 };
      TReal          m_Range[ 2 ] { 0, 255 };
      TReal*         m_Buffer     { nullptr };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__Texture__h__

// eof - $RCSfile$
