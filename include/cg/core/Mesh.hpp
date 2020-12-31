#ifndef CG_CORE_MESH_H
#define CG_CORE_MESH_H

#include <vector>
#include "../math.hpp"

using namespace cg::math;

namespace cg {
	class MeshRenderer;
	class ParticleSystem;
	
	namespace core {
		class Mesh {
		public:
			unsigned int _vbo, // Vertex Buffer
						 _tbo, // Texture Buffer
						 _vao, // Vertex Array
						 _ebo; // Element Buffer
			
			std::vector<Vec3<float>> vertex;
			std::vector<Vec2<float>> uv;
			std::vector<Vec3<unsigned int>> elements;
			
			Mesh();
			~Mesh();
			void bind();
			
			friend class MeshRenderer;
			friend class ParticleSystem;
		};
	}
}

#endif // CG_CORE_MESH_H