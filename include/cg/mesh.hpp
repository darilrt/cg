#ifndef CG_MESH_H
#define CG_MESH_H

#include "core/Mesh.hpp"
#include <iostream>
#include <map>

namespace cg {
	namespace mesh {
		extern std::map<std::string, cg::core::Mesh*> meshes;
		
		cg::core::Mesh* add(std::string name);
		
		cg::core::Mesh* get(std::string name);
	}
}

#endif // CG_MESH_H