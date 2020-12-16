#ifndef CG_CORE_SHADER_H
#define CG_CORE_SHADER_H

#include <iostream>
#include <map>

namespace cg {
	namespace core {
		class Shader {
		public:
			std::string vertex_path;
			std::string fragment_path;

			std::map<std::string, int> uniforms;
			int program;
			
			Shader(const std::string vertex, const std::string fragment);
			void add_uniform(const std::string name);
		};
	}
}

#endif // CG_CORE_SHADER_H