#include "cg/core/camera.hpp"
#include "gl/gl.h"

namespace cg {
	namespace core {
		Camera2D::Camera2D(Window* window) {
			this->rotation = 0;
			this->position = {0, 0};
			this->window = window;
		}

		void Camera2D::use() {
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
			
			glRotated(this->rotation, 0, 0, 1);
			glTranslated(-this->position.x, -this->position.y, 0);
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