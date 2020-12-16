#ifndef CG_CORE_MESH_RENDERER_H
#define CG_CORE_MESH_RENDERER_H

#include <vector>

#include "Mesh.hpp"
#include "Material.hpp"
#include "../math.hpp"

using namespace cg::math;

namespace cg {
	namespace core {
		class MeshRenderer {
		public:
			Vec3<float> position;
			Vec3<float> rotation;
			Vec3<float> scale;
			
			Mesh* mesh;
			
			Material* material;
			
			MeshRenderer();
			MeshRenderer(Material* material);
			MeshRenderer(Mesh* mesh);
			MeshRenderer(Mesh* mesh, Material* material);
			
			void set_material(Material* material);
			void set_material(Mesh* mesh);
			void render();
		};
	}
}

#endif // CG_CORE_MESH_RENDERER_H