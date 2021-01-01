#ifndef CG_GUI_CANVAS_H
#define CG_GUI_CANVAS_H

#include "cg/cg.hpp"
#include "cg/debug.hpp"
#include "cg/display.hpp"
#include "cg/core/Camera.hpp"
#include "cg/components/Sprite.hpp"

namespace cg {
	namespace gui {
		class Canvas : public cg::GameObject {
		public:
			Canvas();
			~Canvas();
			
			void start();
			void update();
			
		private:
			cg::core::Camera* camera;
			cg::Sprite* sprite;
		};
	}
}

#endif // CG_GUI_CANVAS_H