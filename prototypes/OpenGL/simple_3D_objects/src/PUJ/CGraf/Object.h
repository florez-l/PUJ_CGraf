// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__Object__h__
#define __PUJ__CGraf__Object__h__

#include <string>
#include <vector>
#include <PUJ/CGraf/Traits.h>

namespace PUJ
{
  namespace CGraf
  {
    /**
     */
    class Object
    {
    public:
      Object( const std::string& name );
      virtual ~Object( );

      void local_identity( );
      void local_rotate_X( const TReal& t );
      void local_rotate_Y( const TReal& t );
      void local_rotate_Z( const TReal& t );
      void local_rotate( const TReal& t, const TReal& x, const TReal& y, const TReal& z );
      void local_scale( const TReal& x, const TReal& y, const TReal& z );
      void local_translate( const TReal& x, const TReal& y, const TReal& z );
      void parent_identity( );
      void parent_rotate_X( const TReal& t );
      void parent_rotate_Y( const TReal& t );
      void parent_rotate_Z( const TReal& t );
      void parent_rotate( const TReal& t, const TReal& x, const TReal& y, const TReal& z );
      void parent_scale( const TReal& x, const TReal& y, const TReal& z );
      void parent_translate( const TReal& x, const TReal& y, const TReal& z );

      void add_child( Object* child, const TReal& x, const TReal& y, const TReal& z );

      void visibility_off( );
      void visibility_on( );

      void draw( ) const;

    protected:
      void _identity( TReal* M );
      void _rotate( TReal* M, const TReal& t, const TReal& x, const TReal& y, const TReal& z );
      void _scale( TReal* M, const TReal& x, const TReal& y, const TReal& z );
      void _translate( TReal* M, const TReal& x, const TReal& y, const TReal& z );

      virtual void _local_draw( ) const = 0;

    protected:
      std::string m_Name;

      TReal m_LocalTransformation[ 16 ] =
      {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
      };
      TReal m_ParentTransformation[ 16 ] =
      {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
      };

      std::vector< Object* > m_Children;

      bool m_Visibility { true };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__Object__h__

// eof - $RCSfile$
