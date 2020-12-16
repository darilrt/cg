#ifndef CG_INPUT_H
#define CG_INPUT_H

#include "math.hpp"
#include "key_code.hpp"

using namespace cg::math;

namespace cg {
	namespace input {
		bool key_press(key_code);
		bool key_down(key_code);
		bool key_up(key_code);
		
		Vec2<i32> mouse_position();
	}
}

#endif // CG_INPUT_H