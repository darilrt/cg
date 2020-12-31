#ifndef CG_CORE_TEXTURE_H
#define CG_CORE_TEXTURE_H

#include "math.hpp"
#include <iostream>

using namespace cg::math;

namespace cg {
	class Texture {
	public:
		u32 texture;
		Vec2<float> size;
		
		Texture(Vec2<f32> size);
		Texture(const std::string file_path);
		
		~Texture();
		
		static Texture* load(const std::string file_path);
	};
}

#endif // CG_CORE_TEXTURE_H