#include "cg/input.hpp"
#include "cg/display.hpp"

using namespace cg::math;

namespace cg {
	namespace input {
		bool key_press(key_code key) {
			return display::window->key_press(key);
		}
		
		bool key_down(key_code key) {
			return display::window->key_down(key);
		}
		
		bool key_up(key_code key) {
			return display::window->key_up(key);
		}
		
		bool mouse_press(cg::mouse key) {
			return display::window->mouse_press((cg::core::Mouse) key);
		}
		
		bool mouse_down(cg::mouse key) {
			return display::window->mouse_down((cg::core::Mouse) key);
		}
		
		bool mouse_up(cg::mouse key) {
			return display::window->mouse_up((cg::core::Mouse) key);
		}
		
		Vec2<i32> mouse_position() {
			return display::window->mouse_pos();
		}
	}
}
