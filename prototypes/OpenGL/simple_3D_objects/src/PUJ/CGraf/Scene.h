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
    class Camera;
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

      const int* window_size( ) const;
      Camera* camera( )
        {
          return( this->m_Camera );
        }
      const Camera* camera( ) const
        {
          return( this->m_Camera );
        }

      void set_ortho(
        const TReal& left, const TReal& right,
        const TReal& bottom, const TReal& up,
        const TReal& near, const TReal& far
        );
      void set_perspective(
        const TReal& fovy, const TReal& near, const TReal& far
        );

      void init( );
      void project( const int& w, const int& h );
      void draw( );

    protected:
      virtual void _load_scene( ) = 0;

    protected:
      TReal m_Background[ 4 ] = { 0, 0, 0, 0 };
      int m_WindowSize[ 2 ]   = { 700, 700 };

      bool m_UsePerspective { true };
      TReal m_Ortho[ 6 ]       = { -1, 1, -1, 1, -1, 1 };
      TReal m_Perspective[ 3 ] = { 45, 1e-2, 1 };

      PUJ::CGraf::Camera* m_Camera { nullptr };

      PUJ::CGraf::Object* m_Root { nullptr };
      TReal m_Bounds[ 6 ] = { -1, 1, -1, 1, -1, 1 };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGfraf__Scene__h__

// eof - $RCSfile$
