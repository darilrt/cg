#ifndef CG_SPRITE_H
#define CG_SPRITE_H

#include "../cg.hpp"

#include "../core/Material.hpp" 
#include "../core/Shader.hpp"
#include "../core/MeshRenderer.hpp"

namespace cg {
	class Sprite : public cg::Component {
	public:
		cg::Texture* texture;
		cg::core::Shader *shader = nullptr;
		cg::core::Material *material = nullptr;
		cg::core::MeshRenderer *mesh_renderer = nullptr;
		Vec3<f32> position = {0, 0, 0},
				  rotation = {0, 0, 0},
				  scale = {1, 1, 1};
		
		Sprite();
		Sprite(const std::string texture_path);
		~Sprite();
		
		void start();
		void render();
	};
}

#endif // CG_SPRITE_H