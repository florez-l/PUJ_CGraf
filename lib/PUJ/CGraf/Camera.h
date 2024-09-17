// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGfraf__Camera__h__
#define __PUJ__CGfraf__Camera__h__

#include <PUJ/CGraf/Traits.h>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class Camera
    {
    public:
      using Self = Camera;

    public:
      Camera( );
      virtual ~Camera( );

      void set_position( const TReal& x, const TReal& y, const TReal& z );
      void look_at( const TReal& x, const TReal& y, const TReal& z );

      virtual void load( );

    protected:
      TReal m_Position[ 3 ] = { 0, 0, 0 };
      TReal m_LookAt[ 3 ]   = { 0, 0, 0 };
      TReal m_Up[ 3 ]       = { 0, 1, 0 };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGfraf__Camera__h__

// eof - $RCSfile$
