#ifndef CG_CORE_MATERIAL_H
#define CG_CORE_MATERIAL_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <map>

#include "shader.hpp"


namespace cg {
	namespace core {
		class Material;

		class Uniform {
		public:
			std::string name;
			Material* material;
			
			virtual void use() = 0;
		};

		class Material {
		public:
			int _sample_counter;
			std::map<std::string, Uniform*> uniforms;
			Shader* shader;
			
			Material(Shader* shader);
			void set_uniform(std::string name, Uniform* uniform);
			void use();
		};

		// Uniforms

		template<typename T>
		class Uniform1 : public Uniform {
		private:
			void _uniform_call(int value) {
				glUniform1i(this->material->shader->uniforms[this->name], this->value);
			}
			
			void _uniform_call(float value) {
				glUniform1f(this->material->shader->uniforms[this->name], this->value);
			}
			
			void _uniform_call(unsigned int value) {
				glUniform1ui(this->material->shader->uniforms[this->name], this->value);
			}

		public:
			T value;
			
			Uniform1(T value) {
				this->value = value;
			}
			
			void use() {
				_uniform_call(this->value);
			}
		};

		template<typename T>
		class Uniform1v : public Uniform {
		private:
			void _uniform_call(int value) {
				glUniform1iv(
					this->material->shader->uniforms[this->name],
					this->size,
					this->value
				);
			}
			
			void _uniform_call(float value) {
				glUniform1fv(
					this->material->shader->uniforms[this->name],
					this->size,
					this->value
				);
			}
			
			void _uniform_call(unsigned int value) {
				glUniform1uiv(
					this->material->shader->uniforms[this->name],
					this->size,
					this->value
				);
			}

		public:
			T* value;
			int size;
			
			Uniform1v(T* value, int size) {
				this->value = value;
				this->size = size;
			}
			
			void use() {
				_uniform_call(this->value);
			}
		};

		class Uniform1i : public Uniform {
		public:
			int value;

			Uniform1i(int value=0);
			void use() override;
		};

		class Uniform1iv : public Uniform {
		public:
			int size;
			int* value;

			Uniform1iv(int* value=0, int size=0);
			void use() override;
		};

		class Uniform1f : public Uniform {
		public:
			float value;

			Uniform1f(float value=0);
			void use() override;
		};

		class Uniform1fv : public Uniform {
		public:
			int size;
			float* value;

			Uniform1fv(float* value=0, int size=0);
			void use() override;
		};

		class Sampler2D : public Uniform {
		public:
			unsigned int value;

			Sampler2D(unsigned int value=0);
			void use() override;
		};
	}
}

#endif // CG_CORE_MATERIAL_H