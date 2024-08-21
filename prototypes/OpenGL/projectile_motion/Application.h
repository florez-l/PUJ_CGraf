// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Application__h__
#define __Application__h__

/**
 */
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
  static void cbk_mouse( int button, int state, int x, int y );
  static void cbk_motion( int x, int y );
  static void cbk_passive_motion( int x, int y );

private:
  inline static int s_WindowSize[ 2 ] = { 700, 700 };
  inline static int s_MainWindowId { -1 };

  inline static Scene* s_Scene { nullptr };
};

#endif // __Application__h__

// eof - $RCSfile$
