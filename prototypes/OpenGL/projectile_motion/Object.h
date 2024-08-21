// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Object__h__
#define __Object__h__

#include <array>
#include <string>
#include <vector>

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

  void set_color( float r, float g, float b );
  void set_color( const std::array< float, 3 >& c );
  void set_draw_mode( int mode );
  void set_draw_mode_to_polygon( );
  void set_draw_mode_to_wireframe( );

  void local_identity( );
  void local_rotate( float t );
  void local_scale( float sx, float sy );
  void local_translate( float tx, float ty );
  void parent_identity( );
  void parent_rotate( float t );
  void parent_scale( float sx, float sy );
  void parent_translate( float tx, float ty );

  void add_child( Object* child, float px, float py );

  void visibility_off( );
  void visibility_on( );

  void draw( ) const;

  void set_point( const unsigned int& id, const float& x, const float& y );

protected:
  void _identity( std::array< float, 16 >& M );
  void _rotate( std::array< float, 16 >& M, float t );
  void _scale( std::array< float, 16 >& M, float sx, float sy );
  void _translate( std::array< float, 16 >& M, float tx, float ty );

protected:
  std::string m_Name;
  std::vector< float > m_Points;
  std::array< float, 3 > m_Color { 1, 1, 1 };
  int m_DrawMode { 0 };

  std::array< float, 16 > m_LocalTransformation
    {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };
  std::array< float, 16 > m_ParentTransformation
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
