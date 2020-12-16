#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

#include "cg/core/Mesh.hpp"
#include "cg/core/MeshRenderer.hpp"
#include "cg/core/Material.hpp"
#include "cg/math.hpp"

namespace cg {
	namespace core {
		MeshRenderer::MeshRenderer() {
			this->scale = Vec3<float>(1, 1, 1);
		}

		MeshRenderer::MeshRenderer(Material* material) {
			MeshRenderer();
			this->material = material;
		}

		MeshRenderer::MeshRenderer(Mesh* mesh) {
			MeshRenderer();
			this->mesh = mesh;
		}

		MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) {
			MeshRenderer();
			this->mesh = mesh;
			this->material = material;
		}

		void MeshRenderer::set_material(Material* material) {
			this->material = material;
		}

		void MeshRenderer::render() {
			glPushMatrix();
			glTranslatef(this->position.x, this->position.y, this->position.z);
			
			glRotatef(this->rotation.x, 1, 0, 0);
			glRotatef(this->rotation.y, 0, 1, 0);
			glRotatef(this->rotation.z, 0, 0, 1);
			
			glScalef(this->scale.x, this->scale.y, this->scale.z);
			glColor4f(1, 1, 1, 1);

			this->material->use();
			
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glBindVertexArray(mesh->_vao);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->_vbo);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);
			
			glBindBuffer(GL_ARRAY_BUFFER, mesh->_tbo);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_ebo);
			glDrawElements(GL_TRIANGLES, mesh->elements.size() * 3, GL_UNSIGNED_INT, 0);

			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableVertexAttribArray(0);

			glPopMatrix();
			
			glUseProgram(0);
		}
	}
}