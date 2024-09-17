// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGfraf__TrackballCamera__h__
#define __PUJ__CGfraf__TrackballCamera__h__

#include <PUJ/CGraf/Camera.h>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class TrackballCamera
      : public PUJ::CGraf::Camera
    {
    public:
      using Self = TrackballCamera;
      using Superclass = PUJ::CGraf::Camera;

    public:
      TrackballCamera( );
      virtual ~TrackballCamera( );

      void rotate( const TReal& da );

      virtual void load( ) override;

    protected:
      TReal m_Angle { 0 };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGfraf__TrackballCamera__h__

// eof - $RCSfile$
