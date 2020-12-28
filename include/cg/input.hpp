#ifndef CG_INPUT_H
#define CG_INPUT_H

#include "math.hpp"
#include "key_code.hpp"
#include "mouse.hpp"

using namespace cg::math;

namespace cg {
	namespace input {
		bool key_press(key_code);
		bool key_down(key_code);
		bool key_up(key_code);
		
		bool mouse_press(cg::mouse);
		bool mouse_down(cg::mouse);
		bool mouse_up(cg::mouse);
		
		Vec2<i32> mouse_position();
	}
}

#endif // CG_INPUT_H