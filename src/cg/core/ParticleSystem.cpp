#include <GL/glew.h>
#include <GL/gl.h>
#include <algorithm>

#include "cg/time.hpp"
#include "cg/core/ParticleSystem.hpp"

namespace cg {
	namespace core {
		ParticleSystem::ParticleSystem() {
			glGenBuffers(1, &particles_position_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
			
			glGenBuffers(1, &particles_color_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
			
			glGenBuffers(1, &particles_size_rot_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, particles_size_rot_buffer);
			glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 2 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
			
			max = MAX_PARTICLES;
			mesh = nullptr;
			shader = nullptr;
			material = nullptr;
			particle_accum = 0;
		}
		
		ParticleSystem::~ParticleSystem() {
			glDeleteBuffers(1, &particles_position_buffer);
			glDeleteBuffers(1, &particles_color_buffer);
			glDeleteBuffers(1, &particles_size_rot_buffer);
		}
		
		void ParticleSystem::emit(u32 rate, std::function<void(Particle&)> &spawn_func) {
			particle_accum = particle_accum + rate * cg::time::delta_time;
			i32 new_particles = (i32) particle_accum;
			
			if (particle_accum != 0) {
				particle_accum = particle_accum - ((i32) particle_accum);
			}
			
			if (particle_count >= max) {
				return;
			}
			
			find_unused();
			
			for (int i=last_used; i < last_used + new_particles && i < max; i++) {
				if (particles[i].life_time >= particles[i].max_life_time) {
					particles[i].life_time = 0;
					spawn_func(particles[i]);
				}
			}
		}
		
		void ParticleSystem::update(std::function<void(Particle&)> &update_func) {
			particle_count = 0;
			
			for (int i=0; i < MAX_PARTICLES; i++) {
				Particle &p = particles[i];
				
				p.life_time += cg::time::delta_time;
				if (p.life_time < p.max_life_time) {
					
					update_func(particles[i]);
					
					g_particle_data[4 * particle_count]     = p.position.x;
					g_particle_data[4 * particle_count + 1] = p.position.y;
					g_particle_data[4 * particle_count + 2] = p.position.z;
					g_particle_data[4 * particle_count + 3] = p.life_time;
					
					g_particle_color[4 * particle_count]     = p.color.x;
					g_particle_color[4 * particle_count + 1] = p.color.y;
					g_particle_color[4 * particle_count + 2] = p.color.z;
					g_particle_color[4 * particle_count + 3] = p.color.w;
					
					g_particle_size_rot[2 * particle_count    ] = p.size;
					g_particle_size_rot[2 * particle_count + 1] = p.rotation;
					
					particle_count++;
				}
			}
		}
		
		void ParticleSystem::render() {
			std::sort(&particles[0], &particles[MAX_PARTICLES]);
			
			material->use();
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, particle_count * sizeof(GLfloat) * 4, g_particle_data);
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_size_rot_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, particle_count * sizeof(GLfloat) * 2, g_particle_size_rot);
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
			glBufferSubData(GL_ARRAY_BUFFER, 0, particle_count * sizeof(GLfloat) * 4, g_particle_color);
			
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			
			glBindBuffer(GL_ARRAY_BUFFER, mesh->_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
			glVertexAttribDivisor(1, 1);
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_size_rot_buffer);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glVertexAttribDivisor(2, 1);
			
			glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
			glVertexAttribDivisor(3, 1);
			
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glBindBuffer(GL_ARRAY_BUFFER, mesh->_tbo);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_ebo);
			
			glDrawElementsInstanced(
				GL_TRIANGLES,
				mesh->elements.size() * 3,
				GL_UNSIGNED_INT,
				0,
				particle_count
			);
			
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glUseProgram(0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
		}
		
		i32 ParticleSystem::find_unused() {
			for(int i=last_used; i < MAX_PARTICLES; i++){
				if (particles[i].life_time >= particles[i].max_life_time){
					last_used = i;
					return i;
				}
			}

			for(int i=0; i < last_used; i++){
				if (particles[i].life_time >= particles[i].max_life_time){
					last_used = i;
					return i;
				}
			}

			return 0;
		}
	}
}