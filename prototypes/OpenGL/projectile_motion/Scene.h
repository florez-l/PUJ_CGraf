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
  using Self = Scene;

  enum States
  {
    LOCALIZE = 0,
    AIM,
    FIRE
  };

public:
  Scene( const float& wx, const float& wy );
  virtual ~Scene( );

  void init( );
  void project( const int& w, const int& h );
  void draw( );

  void pick( const float& x, const float& y );
  void shift_state( );

protected:
  void _load_scene( );

protected:
  std::array< float, 4 > m_Background { 0, 0, 0, 0 };
  std::array< float, 4 > m_Bounds     { 0, 0, 0, 0 };

  Object* m_Root       { nullptr };
  Object* m_Frame      { nullptr };
  Object* m_Projectile { nullptr };
  Object* m_AimLine    { nullptr };
  float   m_Radius     { 0 };

  States m_State { Self::LOCALIZE };
};

#endif // __Scene__h__

// eof - $RCSfile$
