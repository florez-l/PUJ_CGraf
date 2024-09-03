// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGfraf__Scene__h__
#define __PUJ__CGfraf__Scene__h__

#include <PUJ/CGraf/Traits.h>





#include <GL/glu.h>




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


      class Camera
      {
      public:
        Camera( )
          {
          }
        virtual ~Camera( )
          {
          }

        void set_position( const TReal& x, const TReal& y, const TReal& z )
          {
            this->m_Position[ 0 ] = x;
            this->m_Position[ 1 ] = y;
            this->m_Position[ 2 ] = z;
          }

        void look_at( const TReal& x, const TReal& y, const TReal& z )
          {
            this->m_LookAt[ 0 ] = x;
            this->m_LookAt[ 1 ] = y;
            this->m_LookAt[ 2 ] = z;
          }

        virtual void load( )
          {
            gluLookAt(
              this->m_Position[ 0 ],
              this->m_Position[ 1 ],
              this->m_Position[ 2 ],
              this->m_LookAt[ 0 ],
              this->m_LookAt[ 1 ],
              this->m_LookAt[ 2 ],
              this->m_Up[ 0 ],
              this->m_Up[ 1 ],
              this->m_Up[ 2 ]
              );
          }

      protected:
        TReal m_Position[ 3 ] = { 0, 0, 0 };
        TReal m_LookAt[ 3 ]   = { 0, 0, 0 };
        TReal m_Up[ 3 ]       = { 0, 1, 0 };
      };
      Camera* m_Camera { nullptr };

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

      PUJ::CGraf::Object* m_Root { nullptr };
      TReal m_Bounds[ 6 ] = { -1, 1, -1, 1, -1, 1 };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGfraf__Scene__h__

// eof - $RCSfile$
