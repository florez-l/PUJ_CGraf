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
  using TNat  = PUJ::CGraf::TNat;
  using TReal = PUJ::CGraf::TReal;

public:
  Scene( int argc, char** argv );
  virtual ~Scene( );

protected:
  virtual void _load_scene( ) override;

protected:
  std::string m_Model;
};

#endif // __Simple3DObject__Scene__h__

// eof - $RCSfile$
