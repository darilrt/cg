#include "cg/shader.hpp"
#include <iostream>

namespace cg {
	namespace shader {
		std::map<std::string, cg::core::Shader*> shaders;
		
		cg::core::Shader* load(
			std::string name,
			std::string vertex,
			std::string fragment
		) {
			shaders[name] = new cg::core::Shader(vertex, fragment);
			
			return shaders[name];
		}
		
		cg::core::Shader* get(std::string name) {
			if (shaders.find(name) == shaders.end()) {
				return nullptr;
			}
			
			return shaders[name];
		}
	}
}