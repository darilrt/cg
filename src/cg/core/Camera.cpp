#include <gl/glew.h>
#include <gl/gl.h>

#include "cg/core/camera.hpp"
#include "cg/debug.hpp"

namespace cg {
	namespace core {
		Camera::Camera(Window* w) : texture(w->size) {
			perspective = false;
			window = w;
			position = 0;
			rotation = 0;
			fovy = 45;
			z_near = -1000;
			z_far = 1000;
			
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.texture, 0);
			
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w->size.x, w->size.y);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			
			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cg::log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		
		void Camera::begin() {
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			this->window->clear();
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			if (perspective) {
				f32 aspect = ((f32) window->size.x) / ((f32) window->size.y);
				gluPerspective(fovy, aspect, z_near, z_far);
			}
			else {
				Vec2<int> n_size = this->window->size / 2;
				glOrtho(-n_size.x, n_size.x, -n_size.y, n_size.y, z_near, z_far);
			}
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			
			glAlphaFunc(GL_GREATER, 0.5);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glPushMatrix();
			glRotated(this->rotation.x, 1, 0, 0);
			glRotated(this->rotation.y, 0, 1, 0);
			glRotated(this->rotation.z, 0, 0, 1);
			
			glTranslated(-this->position.x, -this->position.y, this->position.z);
		}
		
		void Camera::end() {
			glPopMatrix();
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);
		}

		Vec3<f32> Camera::screen2d_to_world(Vec3<i32> pos) {
			Vec3<int> n_size(this->window->size / 2, 0);
			
			return Vec3<f32>(
				pos.x + this->position.x - n_size.x,
				-(pos.y - this->position.y - n_size.y),
				0
			);
		}
		
	}
}