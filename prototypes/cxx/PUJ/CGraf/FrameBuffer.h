// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__FrameBuffer__h__
#define __PUJ__CGraf__FrameBuffer__h__

#include <string>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class FrameBuffer
    {
    public:
      using Self = FrameBuffer;

      enum ColorDeep
      {
        BINARY,
        GRAY,
        RGB
      };

    public:
      FrameBuffer(
        const unsigned short& width = 512,
        const unsigned short& height = 512,
        const ColorDeep& color_deep = Self::RGB
        );
      FrameBuffer( const Self& other );
      Self& operator=( const Self& other );
      virtual ~FrameBuffer( );

      void random_fill( );

      Self& operator+( const Self& other ) const;
      Self& operator+=( const Self& other );

      Self& operator-( const Self& other ) const;
      Self& operator-=( const Self& other );

      Self& operator*( const Self& other ) const;
      Self& operator*=( const Self& other );

      Self& operator/( const Self& other ) const;
      Self& operator/=( const Self& other );

      bool save_as_netpbm( const std::string& fname );
      bool load_from_netpbm( const std::string& fname );

    protected:
      ColorDeep      m_ColorDeep;
      unsigned short m_Dims[ 3 ];
      unsigned char* m_Buffer { nullptr };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__FrameBuffer__h__

// eof - $RCSfile$
