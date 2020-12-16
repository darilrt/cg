#ifndef CG_CORE_CAMERA_H
#define CG_CORE_CAMERA_H

#include <iostream>
#include <SDL2/SDL.h>

#include "../math.hpp"
#include "Window.hpp"

using namespace cg::math;

namespace cg {
	namespace core {
		class Camera2D {
		public:
			Window* window;
			Vec2<f32> position;
			f32 rotation;
			
			Camera2D(Window* window);
			
			void use();
			Vec2<f32> screen_to_world(Vec2<i32> pos);
			
			inline void depth_test(bool enable) {
				window->depth_test(enable);
			}
		};
	}
}

#endif // CG_CORE_CAMERA_H