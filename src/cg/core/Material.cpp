#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>

#include "cg/core/material.hpp"

// Material

namespace cg {
	namespace core {
		Material::Material(Shader* shader) {
			this->shader = shader;
		}

		void Material::set_uniform(std::string name, Uniform* uniform) {
			uniform->name = name;
			uniform->material = this;
			
			this->uniforms[name] = uniform;
		}

		void Material::use() {
			glUseProgram(this->shader->program);
			
			this->_sample_counter = 0;
			for(auto ele : this->uniforms) {
				ele.second->use();
			}
		}

		// Uniforms

		// 1i

		Uniform1i::Uniform1i(int value) {
			this->value = value;
		}

		void Uniform1i::use() {
			glUniform1i(
				this->material->shader->uniforms[this->name],
				this->value
			);
		}

		// 1iv

		Uniform1iv::Uniform1iv(int* value, int size) {
			this->value = value;
			this->size = size;
		}

		void Uniform1iv::use() {
			glUniform1iv(
				this->material->shader->uniforms[this->name],
				this->size,
				this->value
			);
		}

		// 1f

		Uniform1f::Uniform1f(float value) {
			this->value = value;
		}

		void Uniform1f::use() {
			glUniform1f(
				this->material->shader->uniforms[this->name],
				this->value
			);
		}

		// 1fv

		Uniform1fv::Uniform1fv(float* value, int size) {
			this->value = value;
			this->size = size;
		}

		void Uniform1fv::use() {
			glUniform1fv(
				this->material->shader->uniforms[this->name],
				this->size,
				this->value
			);
		}

		// Sampler2D

		Sampler2D::Sampler2D(unsigned int texture) {
			this->value = texture;
		}

		void Sampler2D::use() {
			glActiveTexture(GL_TEXTURE0 + this->material->_sample_counter);
			glBindTexture(GL_TEXTURE_2D, this->value);
			
			glUniform1i(
				this->material->shader->uniforms[this->name],
				this->material->_sample_counter
			);
			
			this->material->_sample_counter++;
		}
	}
}