#include <GL/glew.h>
#include <GL/gl.h>

#include "cg/components/ParticleEmitter.hpp"
#include "cg/core/Mesh.hpp"
#include "cg/core/Shader.hpp"
#include "cg/core/Material.hpp"

namespace cg {
	ParticleEmitter::ParticleEmitter() {
			max = MAX_PARTICLES;
		}
	
	ParticleEmitter::ParticleEmitter(const std::string texture_path) {
		texture = new cg::Texture(texture_path);
			max = MAX_PARTICLES;
	}
	
	void ParticleEmitter::start() {
		particle = new cg::core::ParticleSystem();
		
		if (particle->shader == nullptr) {
			if ((particle->shader = cg::shader::get("particle")) == nullptr) {
				particle->shader = cg::shader::load(
					"particle",
					"assets/shaders/particle.vert",
					"assets/shaders/particle.frag"
				);
				particle->shader->add_uniform("texture");
				particle->shader->add_uniform("use_texture");
			}
		}
		
		if (particle->material == nullptr) {
			particle->material = new cg::core::Material(particle->shader);
			
			if (texture) {
				particle->material->set_uniform(
					"texture",
					new cg::core::Sampler2D(texture->texture)
				);
			}
			
			particle->material->set_uniform(
				"use_texture",
				new cg::core::Uniform1i(texture != nullptr ? 1 : 0)
			);
		}
		
		if (particle->mesh == nullptr) {
			particle->mesh = new cg::core::Mesh();
			
			particle->mesh->vertex = {
				{-0.5, -0.5, 0},
				{-0.5,  0.5, 0},
				{ 0.5,  0.5, 0},
				{ 0.5, -0.5, 0},
			};
			
			particle->mesh->uv = {
				{0, 1},
				{0, 0},
				{1, 0},
				{1, 1},
			};
			
			particle->mesh->elements = {
				{2, 1, 0},
				{0, 3, 2},
			};
			
			particle->mesh->bind();
		}
	}
	
	void ParticleEmitter::update() {
		particle->max = max;
		
		if (is_emitting) particle->emit(rate, spawn_func);
		
		particle->update(update_func);
	}
	
	void ParticleEmitter::render() {
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
		
		particle->render();
		glPopMatrix();
	}

	ParticleEmitter::~ParticleEmitter() {
		delete particle->mesh;
		delete particle;
	}
}