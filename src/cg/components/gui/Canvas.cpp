#include "cg/components/gui/Canvas.hpp"

namespace cg {
	namespace gui {
		Canvas::Canvas() {
			camera = new cg::core::Camera(cg::display::window);
		}

		Canvas::~Canvas() {
			delete camera;
		}

		void Canvas::start() {
			regist(sprite = new cg::Sprite(&camera->texture));
			sprite->position.z = -999;
			sprite->scale.y = -1;
		}

		void Canvas::update() {
			camera->begin();
			
			camera->end();
		}
	}
}