#include "cg/mesh.hpp"
#include <iostream>

namespace cg {
	namespace mesh {
		std::map<std::string, cg::core::Mesh*> meshes;
		
		cg::core::Mesh* add(std::string name) {
			meshes[name] = new cg::core::Mesh();
			
			return meshes[name];
		}
		
		cg::core::Mesh* get(std::string name) {
			if (meshes.find(name) == meshes.end()) {
				return nullptr;
			}
			
			return meshes[name];
		}
	}
}