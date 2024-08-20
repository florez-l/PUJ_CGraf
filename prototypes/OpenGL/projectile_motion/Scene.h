// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Scene__h__
#define __Scene__h__

#include <array>
#include "Object.h"

/**
 */
class Scene
{
public:
  Scene( const float& wx, const float& wy );
  virtual ~Scene( );

  void init( );
  void update_projection( );
  void draw( );

protected:
  void _load_scene( );

protected:
  std::array< float, 4 > m_BackgroundColor { 0, 0, 0, 0 };
  std::array< float, 4 > m_WorldBounds     { 0, 0, 0, 0 };

  Object* m_Root { nullptr };
};

#endif // __Scene__h__

// eof - $RCSfile$
