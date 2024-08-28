// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGfraf__Scene__h__
#define __PUJ__CGfraf__Scene__h__

#include <PUJ/CGraf/Traits.h>

namespace PUJ
{
  namespace CGraf
  {
    // Some forward declarations
    class Object;

    /**
     */
    class Scene
    {
    public:
      using Self = Scene;

    public:
      Scene( int argc, char** argv );
      virtual ~Scene( );

      void init( );
      void project( const int& w, const int& h );
      void draw( );

    protected:
      virtual void _load_scene( ) = 0;

    protected:
      TReal m_Background[ 4 ] = { 0, 0, 0, 0 };
      TReal m_Bounds[ 6 ]     = { -1, 1, -1, 1, -1, 1 };

      PUJ::CGraf::Object* m_Root { nullptr };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGfraf__Scene__h__

// eof - $RCSfile$
