#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "cg/core/Mesh.hpp"

namespace cg {
	namespace core {
		Mesh::Mesh() {
			glGenBuffers(1, &this->_ebo);
			glGenBuffers(1, &this->_tbo);
			glGenBuffers(1, &this->_vbo);
			
			glGenVertexArrays(1, &this->_vao);
		}
		
		Mesh::~Mesh() {
			glDeleteBuffers(1, &this->_ebo);
			glDeleteBuffers(1, &this->_tbo);
			glDeleteBuffers(1, &this->_vbo);
			
			glDeleteVertexArrays(1, &this->_vao);
		}

		void Mesh::bind() {
			glBindVertexArray(this->_vao);
			
			// Elements buffer
			if (this->elements.size()) {
				glBindBuffer(GL_ARRAY_BUFFER, this->_ebo);
				glBufferData(GL_ARRAY_BUFFER, this->elements.size() * 12, &this->elements[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			
			// Texture buffer
			if (this->uv.size()) {
				glBindBuffer(GL_ARRAY_BUFFER, this->_tbo);
				glBufferData(GL_ARRAY_BUFFER, this->uv.size() * 12, &this->uv[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			// Vertex buffer
			if (this->vertex.size()) {
				glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
				glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * 12, &this->vertex[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			
			glBindVertexArray(0);
		}
	}
}