// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Object__h__
#define __Object__h__

#include <string>
#include <vector>

#include "Traits.h"

/**
 */
class Object
{
public:
  Object(
    const std::string& name,
    const std::string& primitive = "none", unsigned int samples = 50
    );
  virtual ~Object( );

  void set_color( const TReal& r, const TReal& g, const TReal& b );
  void set_color( const TReal* c );
  void set_draw_mode( int mode );
  void set_draw_mode_to_polygon( );
  void set_draw_mode_to_wireframe( );

  void local_identity( );
  void local_rotate( const TReal& t );
  void local_scale( const TReal& sx, const TReal& sy );
  void local_translate( const TReal& tx, const TReal& ty );
  void parent_identity( );
  void parent_rotate( const TReal& t );
  void parent_scale( const TReal& sx, const TReal& sy );
  void parent_translate( const TReal& tx, const TReal& ty );

  void add_child( Object* child, const TReal& px, const TReal& py );

  void visibility_off( );
  void visibility_on( );

  void draw( ) const;

  void set_point( const unsigned int& id, const TReal& x, const TReal& y );

protected:
  void _identity( TReal* M );
  void _rotate( TReal* M, const TReal& t );
  void _scale( TReal* M, const TReal& sx, const TReal& sy );
  void _translate( TReal* M, const TReal& tx, const TReal& ty );

protected:
  std::string m_Name;
  std::vector< TReal > m_Points;
  TReal m_Color[ 3 ] = { 1, 1, 1 };
  int m_DrawMode { 0 };

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

#endif // __Object__h__

// eof - $RCSfile$
