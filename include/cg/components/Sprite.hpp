#ifndef CG_SPRITE_H
#define CG_SPRITE_H

#include "../core/Material.hpp" 
#include "../core/Shader.hpp"
#include "../core/MeshRenderer.hpp"
#include "../Texture.hpp"
#include "../Component.hpp"
#include "../shader.hpp"
#include "../material.hpp"
#include "../mesh.hpp"
#include "../math.hpp"

using namespace cg::math;

namespace cg {
	class Sprite : public cg::Component {
	public:
		static cg::core::Mesh *mesh;
		static cg::core::Shader *shader;
		static cg::core::Material *material;
		static cg::core::MeshRenderer *mesh_renderer;
		
		bool is_global;
	
		cg::Texture* texture;
		Vec3<f32> position = {0, 0, 0},
				  rotation = {0, 0, 0},
				  scale = {1, 1, 1};
		
		Sprite();
		Sprite(const std::string texture_path);
		Sprite(cg::Texture* texture);
		~Sprite();
		
		void start();
		void render();
		
	private:
		bool texture_d;
	};
}

#endif // CG_SPRITE_H