#include <gl/glew.h>
#include <gl/gl.h>

#include "cg/core/camera.hpp"
#include "cg/debug.hpp"

namespace cg {
	namespace core {
		Camera2D::Camera2D(Window* window) : texture(window->size) {
			this->rotation = 0;
			this->position = {0, 0};
			this->window = window;
			
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.texture, 0);
			
			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window->size.x, window->size.y);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			
			if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				cg::log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Camera2D::begin() {
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			this->window->clear();
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			Vec2<int> n_size = this->window->size / 2;
			glOrtho(-n_size.x, n_size.x, -n_size.y, n_size.y, -1000, 1000);
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			
			glAlphaFunc(GL_GREATER, 0.5);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			glPushMatrix();
			
			glRotated(this->rotation, 0, 0, 1);
			glTranslated(-this->position.x, -this->position.y, 0);
		}
		
		void Camera2D::end() {
			glPopMatrix();
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			glDisable(GL_DEPTH_TEST);
		}

		Vec2<f32> Camera2D::screen_to_world(Vec2<i32> pos) {
			Vec2<int> n_size = this->window->size / 2;
			
			return Vec2<f32>(
				pos.x + this->position.x - n_size.x,
				-(pos.y - this->position.y - n_size.y)
			);
		}
	}
}