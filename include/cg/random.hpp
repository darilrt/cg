#ifndef G_RANDOM_H
#define G_RANDOM_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#include "math.hpp"

using namespace cg::math;

namespace cg {
	f32 random(i32 min, i32 max, f32 res=1);
}

#endif // G_RANDOM_H