#include "cg/debug.hpp"
#include "cg/random.hpp"

namespace cg {
	f32 random(i32 min, i32 max, f32 res)  {
		float d = 1 / res;
		max *= d;
		min *= d;
		
		auto t = ((f32) (std::rand() % (max - min + 1) + min)) / d;
		return t;
	}
}