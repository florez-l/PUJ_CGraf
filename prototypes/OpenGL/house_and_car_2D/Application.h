// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Application__h__
#define __Application__h__

#include <array>
#include "Scene.h"

/**
 */
class Application
{
public:
  using Self = Application;

public:
  static void init( int argc, char** argv );
  static void go( );

private:
  static void cbk_display( );
  static void cbk_keyboard( unsigned char key, int x, int y );
  static void cbk_reshape( int width, int height );

private:
  inline static std::array< int, 2 > s_WindowSize { 1024, 600 };
  inline static int s_MainWindowId { -1 };

  inline static Scene* s_Scene { nullptr };
};

#endif // __Application__h__

// eof - $RCSfile$
