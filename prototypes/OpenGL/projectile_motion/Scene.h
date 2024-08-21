// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Scene__h__
#define __Scene__h__

#include <chrono>

#include "Traits.h"

/**
 */
class Object;

/**
 */
class Scene
{
public:
  using Self = Scene;

  enum States
  {
    LOCALIZE,
    AIM,
    FIRE
  };

public:
  Scene( int argc, char** argv );
  virtual ~Scene( );

  void init( );
  void project( const int& w, const int& h );
  void draw( );

  void pick( const TReal& x, const TReal& y );
  void shift_state( );

protected:
  void _load_scene( );

protected:
  TReal m_Background[ 4 ] = { 0, 0, 0, 0 };
  TReal m_Bounds[ 4 ]     = { 0, 100, 0, 100 };
  TReal m_Gravity[ 2 ]    = { 0, 9.8 };
  TReal m_GravityNorm;

  Object* m_Root       { nullptr };
  Object* m_Frame      { nullptr };
  Object* m_Projectile { nullptr };
  Object* m_AimLine    { nullptr };
  TReal   m_Radius     { 0 };

  States m_State { Self::LOCALIZE };

  std::chrono::steady_clock::time_point m_StartTime;
  TReal m_V0[ 4 ] = { 0, 0, 0, 0 };
};

#endif // __Scene__h__

// eof - $RCSfile$
