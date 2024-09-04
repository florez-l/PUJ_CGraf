// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Simple3DObject__Application__h__
#define __Simple3DObject__Application__h__

// Some forward declarations
class Scene;

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
  static void cbk_idle( );
  static void cbk_display( );
  static void cbk_keyboard( unsigned char key, int x, int y );
  static void cbk_reshape( int width, int height );

private:
  inline static int s_MainWindowId { -1 };

  inline static Scene* s_Scene { nullptr };
};

#endif // __Simple3DObject__Application__h__

// eof - $RCSfile$
