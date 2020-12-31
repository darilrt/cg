#include "cg/material.hpp"
#include <iostream>

namespace cg {
	namespace material {
		std::map<std::string, cg::core::Material*> materials;
		
		cg::core::Material* add(std::string name, cg::core::Shader* shader) {
			materials[name] = new cg::core::Material(shader);
			
			return materials[name];
		}
		
		cg::core::Material* get(std::string name) {
			if (materials.find(name) == materials.end()) {
				return nullptr;
			}
			
			return materials[name];
		}
	}
}