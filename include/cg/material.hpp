#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H

#include "core/Shader.hpp"
#include "core/Material.hpp"
#include <iostream>
#include <map>

namespace cg {
	namespace material {
		extern std::map<std::string, cg::core::Material*> materials;
		
		cg::core::Material* add(std::string name, cg::core::Shader* shader);
		
		cg::core::Material* get(std::string name);
	}
}

#endif // CG_MATERIAL_H