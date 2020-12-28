#ifndef CG_CORE_PARTICLE_SYSTEM_H
#define CG_CORE_PARTICLE_SYSTEM_H

#include "../math.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"

#include <functional>

#define MAX_PARTICLES 2500

using namespace cg::math;

namespace cg {
	namespace core {
		struct Particle {
			Vec3<f32> position,
					  speed;
		  
			Vec4<f32> color;
			
			f32 life_time = 0,
				max_life_time = 0,
				size = 0,
				rotation = 0;
			
			bool operator<(Particle& that){
				return this->life_time > that.life_time;
			}
		};

		class ParticleSystem {
		public:
			u32 max;

			Shader *shader;
			Material *material;
			Mesh *mesh;
			
			ParticleSystem();
			~ParticleSystem();
			
			void emit(u32 rate, std::function<void(Particle&)> &spawn_func);
			void update(std::function<void(Particle&)> &update_func);
			void render();
			
		private:
			
			f32 particle_accum;
			i32 find_unused();
			
			i32 last_used = 0;
			
			Particle particles[MAX_PARTICLES];
			
			u32 particles_position_buffer,
				particles_color_buffer,
				particles_size_rot_buffer;
					
			f32	g_particle_data[MAX_PARTICLES * 4],
				g_particle_color[MAX_PARTICLES * 4],
				g_particle_size_rot[MAX_PARTICLES * 2];
			
			u32 particle_count;
		};
	}
}

#endif // CG_CORE_PARTICLE_SYSTEM_H