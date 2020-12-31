#include <GL/glew.h>
#include <GL/gl.h>

#include "cg/components/Sprite.hpp"

cg::core::Sampler2D* material_texture = nullptr;

namespace cg {
	cg::core::Mesh *Sprite::mesh = nullptr;
	cg::core::Shader *Sprite::shader = nullptr;
	cg::core::Material *Sprite::material = nullptr;
	cg::core::MeshRenderer *Sprite::mesh_renderer = nullptr;
	
	Sprite::Sprite() {}
	
	Sprite::Sprite(const std::string texture_path) {
		texture = new cg::Texture(texture_path);
		texture_d = true;
		is_global = false;
	}
	
	Sprite::Sprite(cg::Texture* _texture) {
		texture = _texture;
		texture_d = false;
		is_global = false;
	}

	Sprite::~Sprite() {
		if (texture_d) delete texture;
	}
	
	void Sprite::start() {
		if (Sprite::shader == nullptr) {
			if ((Sprite::shader = cg::shader::get("standar")) == nullptr) {
				Sprite::shader = cg::shader::load(
					"standar",
					"assets/shaders/standar.vert",
					"assets/shaders/standar.frag"
				);
				Sprite::shader->add_uniform("texture");
			}
		}
		
		if (Sprite::material == nullptr) {
			if ((Sprite::material = cg::material::get("standar")) == nullptr) {
				Sprite::material = cg::material::add("standar", shader);
				
				material_texture = new cg::core::Sampler2D(0);
				
				Sprite::material->set_uniform(
					"texture",
					material_texture
				);
			}
		}
	
		if (Sprite::mesh_renderer == nullptr) {
			if ((Sprite::mesh = cg::mesh::get("sprite")) == nullptr) {
				Sprite::mesh = cg::mesh::add("sprite");
				
				Sprite::mesh->vertex = {
					{-0.5, -0.5, 0},
					{-0.5,  0.5, 0},
					{ 0.5,  0.5, 0},
					{ 0.5, -0.5, 0},
				};
				
				Sprite::mesh->uv = {
					{0, 1},
					{0, 0},
					{1, 0},
					{1, 1},
				};
				
				Sprite::mesh->elements = {
					{2, 1, 0},
					{0, 3, 2},
				};
				
				Sprite::mesh->bind();
			}
			
			Sprite::mesh_renderer = new cg::core::MeshRenderer(Sprite::mesh, Sprite::material);
		}
	}

	void Sprite::render() {
		material_texture->value = texture->texture;
		
		mesh_renderer->position = position;
		
		mesh_renderer->scale = {
			texture->size.x * game_object->scale.x * scale.x,
			texture->size.y * game_object->scale.y * scale.y,
			game_object->scale.z * scale.z
		};
		
		mesh_renderer->rotation = rotation;
		
		glPushMatrix();
		if (!is_global) {
			Vec3<f32> pos = game_object->world_position();
			
			glTranslatef(
				pos.x,
				pos.y,
				pos.z
			);
			
			glRotatef(game_object->rotation.x, 1, 0, 0);
			glRotatef(game_object->rotation.y, 0, 1, 0);
			glRotatef(game_object->rotation.z, 0, 0, 1);
			
			glScalef(
				game_object->scale.x,
				game_object->scale.y,
				game_object->scale.z
			);
		}
		
		mesh_renderer->render();
		glPopMatrix();
	}
}