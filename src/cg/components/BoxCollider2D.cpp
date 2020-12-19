#include "cg/components/BoxCollider2D.hpp"

namespace cg {
	BoxCollider2D::BoxCollider2D(bool s) {
		rect.position = {0, 0};
		rect.size = {0, 0};
		rect.rotation = 0;
		is_static = s;
	}
	
	BoxCollider2D::BoxCollider2D(const Vec2<f32> p, const Vec2<f32> s, bool _s) {
		rect.position = p;
		rect.size = s;
		rect.rotation = 0;
		is_static = _s;
	}
	
	cg::physics::Rect2D* BoxCollider2D::_get_bounding_box() {
		cg::physics::Rect2D* r = new cg::physics::Rect2D();
		
		if (rotation == 0) {
			r->position = position;
			r->size = rect.size;
			r->rotation = 0;
		}
		else {
			f32 max_x = max(rect[0].x, max(rect[1].x, max(rect[2].x, rect[3].x))),
				min_x = min(rect[0].x, min(rect[1].x, min(rect[2].x, rect[3].x))),
				max_y = max(rect[0].y, max(rect[1].y, max(rect[2].y, rect[3].y))),
				min_y = min(rect[0].y, min(rect[1].y, min(rect[2].y, rect[3].y)));
			
			r->size = {max_x - min_x, max_y - min_y};
			r->position = Vec2<f32>(min_x, min_y) + (r->size / 2);
			r->rotation = 0;
		}
		
		return r;
	}
	
	void BoxCollider2D::debug()  {
		rect.rotation = rotation;
		rect.position = position;
		
		cg::debug::polygon({.1, .1, 1}, {
			rect[0], rect[1], rect[2], rect[3]
		}, true);
		
		cg::physics::Rect2D* r = _get_bounding_box();
		
		cg::debug::polygon({1, 1, 1}, {
			r->get(0), r->get(1), r->get(2), r->get(3)
		}, true);
	}
}