// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__Viewport__h__
#define __PUJ__CGraf__Viewport__h__

#include <PUJ/CGraf/FrameBuffer.h>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class Viewport
      : public PUJ::CGraf::FrameBuffer
    {
    public:
      using Self = Viewport;
      using Superclass = PUJ::CGraf::FrameBuffer;

    public:
      Viewport(
        const unsigned short& width = 512,
        const unsigned short& height = 512,
        const ColorDeep& color_deep = Self::RGB
        );
      Viewport( const Self& other );
      Self& operator=( const Self& other );
      virtual ~Viewport( ) = default;

      bool isInside( const unsigned short& x, const unsigned short& y ) const;

      const float& get(
        const unsigned short& x, const unsigned short& y
        ) const;
      void set(
        const unsigned short& x, const unsigned short& y, const float& v
        );
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__Viewport__h__

// eof - $RCSfile$
