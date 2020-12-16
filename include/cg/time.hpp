#ifndef CG_TIME_H
#define CG_TIME_H

#include "math.hpp"
#include "Timer.hpp"

using namespace cg::math;

namespace cg {
	namespace time {
		extern f32 delta_time, life_time;
		extern i32 fps;
	}
}

#endif // CG_TIME_H