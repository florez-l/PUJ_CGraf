// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Simple3DObject__Scene__h__
#define __Simple3DObject__Scene__h__

#include <string>
#include <PUJ/CGraf/Scene.h>

/**
 */
class Scene
  : public PUJ::CGraf::Scene
{
public:
  using Self = Scene;
  using Superclass = PUJ::CGraf::Scene;

public:
  using TNat  = PUJ::CGraf::TNat;
  using TReal = PUJ::CGraf::TReal;

public:
  Scene( int argc, char** argv );
  virtual ~Scene( );

  virtual void init( ) override;

protected:
  virtual void _load_scene( ) override;

protected:
  std::string m_Model;

  TReal m_AmbientLight[ 4 ] = { 1, 1, 1, 1 };
};

#endif // __Simple3DObject__Scene__h__

// eof - $RCSfile$
