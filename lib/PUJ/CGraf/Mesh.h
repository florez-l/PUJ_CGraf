// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __PUJ__CGraf__Mesh__h__
#define __PUJ__CGraf__Mesh__h__

#include <PUJ/CGraf/Object.h>

namespace PUJ
{
  namespace CGraf
  {
    class Texture;

    /**
     */
    class Mesh
      : public PUJ::CGraf::Object
    {
    public:
      using Self       = Mesh;
      using Superclass = PUJ::CGraf::Object;

      enum DrawMode
      {
        Points,
        Wireframe,
        Surface,
        SurfaceWithWireframe
      };

    public:
      Mesh( const std::string& name );
      virtual ~Mesh( );

      void set_drawmode_to_points( );
      void set_drawmode_to_wireframe( );
      void set_drawmode_to_surface( );
      void set_drawmode_to_surface_with_wireframe( );

      void set_color( const TReal& r, const TReal& g, const TReal& b );
      void set_color( const TReal* c );

      void load_bounding_box( TReal* b ) const;

      void load_from_OBJ( const std::string& fname );

    protected:
      virtual void _local_draw( ) const override;

    protected:
      Self::DrawMode m_DrawMode { Self::Wireframe };

      TReal m_Color[ 3 ] = { 1, 1, 1 };

      std::vector< TReal > m_Points;
      std::vector< TReal > m_Normals;
      std::vector< TReal > m_Textures;
      std::vector< TNat >  m_Triangles;
      std::vector< TNat >  m_Quads;
      std::vector< TNat >  m_Polygons;
      std::vector< TNat >  m_PolygonSizes;

      PUJ::CGraf::Texture* m_Texture { nullptr };
    };
  } // end namespace
} // end namespace

#endif // __PUJ__CGraf__Mesh__h__

// eof - $RCSfile$
