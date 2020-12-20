#include <GL/glew.h>
#include <GL/gl.h>

#include "cg/components/Sprite.hpp"

namespace cg {
	Sprite::Sprite() {}
	
	Sprite::Sprite(const std::string texture_path) {
		texture = new cg::Texture(texture_path);
		is_global = false;
	}

	Sprite::~Sprite() {
		delete texture;
		delete material;
		delete mesh_renderer;
	}
	
	void Sprite::start() {
		if (shader == nullptr) {
			if ((shader = cg::shader::get("standar")) == nullptr) {
				shader = cg::shader::load(
					"standar",
					"assets/shaders/standar.vert",
					"assets/shaders/standar.frag"
				);
				shader->add_uniform("texture");
			}
		}
		
		if (material == nullptr) {
			material = new cg::core::Material(shader);
			material->set_uniform(
				"texture",
				new cg::core::Sampler2D(texture->texture)
			);
		}
	
		if (mesh_renderer == nullptr) {
			cg::core::Mesh *mesh = new cg::core::Mesh();
			
			mesh->vertex = {
				{-0.5, -0.5, 0},
				{-0.5,  0.5, 0},
				{ 0.5,  0.5, 0},
				{ 0.5, -0.5, 0},
			};
			
			mesh->uv = {
				{0, 1},
				{0, 0},
				{1, 0},
				{1, 1},
			};
			
			mesh->elements = {
				{2, 1, 0},
				{0, 3, 2},
			};
			
			mesh->bind();
			
			mesh_renderer = new cg::core::MeshRenderer(mesh, material);
		}
	}

	void Sprite::render() {
		mesh_renderer->position = position;
		
		mesh_renderer->scale = {
			texture->size.x * game_object->scale.x * scale.x,
			texture->size.y * game_object->scale.y * scale.y,
			game_object->scale.z * scale.z
		};
		
		mesh_renderer->rotation = rotation;
		
		glPushMatrix();
		if (!is_global) {
			glTranslatef(
				game_object->position.x,
				game_object->position.y,
				game_object->position.z
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