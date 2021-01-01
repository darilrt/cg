#ifndef CG_CORE_CAMERA_H
#define CG_CORE_CAMERA_H

#include <iostream>
#include <SDL2/SDL.h>
#include "Shader.hpp"
#include "Material.hpp"
#include "MeshRenderer.hpp"
#include "Window.hpp"
#include "../math.hpp"
#include "../Texture.hpp"

using namespace cg::math;

namespace cg {
	namespace core {
		class Camera {
		public:
			bool perspective;
			f32 fovy, z_near, z_far;
			
			Vec3<f32> position;
			Vec3<f32> rotation;
			
			Camera(Window* window);
			
			void begin();
			void end();
			Vec3<f32> screen2d_to_world(Vec3<i32> pos);
			
			inline void depth_test(bool enable) {
				window->depth_test(enable);
			}
			
			cg::Texture texture;
		
		private:
			Window* window;
			u32 fbo, rbo;
		};
	}
}

#endif // CG_CORE_CAMERA_H