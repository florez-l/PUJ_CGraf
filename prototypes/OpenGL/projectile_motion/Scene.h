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
  Scene( );
  virtual ~Scene( );

  void init( );
  void update_projection( );
  void draw( );

protected:
  void _load_scene( );

protected:
  std::array< float, 4 > m_BackgroundColor {  1,  1,  1, 0 };
  std::array< float, 4 > m_WorldBounds     { -1, 16, -1, 8 };

  Object* m_Root { nullptr };
};

#endif // __Scene__h__

// eof - $RCSfile$
