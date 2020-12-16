#ifndef CG_DISPLAY_H
#define CG_DISPLAY_H

#include "math.hpp"
#include "cg/core/Window.hpp"

#include <iostream>

using namespace cg::math;

namespace cg {
	namespace display {
		extern f32 width, height;
		extern core::Window* window;
		
		void init(Vec2<i32> resolution);
		void title(const std::string title);
		void icon(const std::string icon_path);
		void background(const Vec4<f32> color);
	}
}

#endif // CG_DISPLAY_H