#ifndef CG_SHADER_H
#define CG_SHADER_H

#include "core/Shader.hpp"
#include <iostream>
#include <map>

namespace cg {
	namespace shader {
		extern std::map<std::string, cg::core::Shader*> shaders;
		
		cg::core::Shader* load(
			std::string name,
			std::string vertex,
			std::string fragment
		);
		
		cg::core::Shader* get(std::string name);
	}
}

#endif // CG_SHADER_H