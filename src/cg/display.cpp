#include <exception>
#include <cstdlib>
#include <ctime>

#include "cg/display.hpp"
#include "cg/core/Window.hpp"

using namespace cg::math;

namespace cg {
	namespace display {
		f32 width = 0, height = 0;
		core::Window* window = nullptr;
		
		void init(Vec2<i32> resolution) {
			std::srand(std::time(nullptr));
			
			if (window == nullptr) {
				window = new cg::core::Window(
					"Untitle Game",
					resolution
				);
				window->color = Vec4<f32>(0.125, 0.125, 0.125, 1);
			}
			
			width = resolution.x, height = resolution.y;
		}
		
		void title(const std::string title) {
			// Check window was intialized ---------------------
			if (window == nullptr) {
				init({800, 600});
			}
			
			window->title(title);
		}
		
		void background(const Vec4<f32> color) {
			// Check window was intialized ---------------------
			if (window == nullptr) {
				init({800, 600});
			}
			
			window->color = color;
		}
		
		void icon(const std::string icon_path) {}
	}
}
