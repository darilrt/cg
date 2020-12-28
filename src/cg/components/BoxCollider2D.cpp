#include "cg/components/BoxCollider2D.hpp"

namespace cg {
	BoxCollider2D::BoxCollider2D(bool s) {
		position = {0, 0};
		rotation = 0;
		size = {0, 0};
		is_static = s;
	}
	
	BoxCollider2D::BoxCollider2D(const Vec2<f32> p, const Vec2<f32> s, bool _s) {
		position = p;
		rotation = 0;
		size = s;
		is_static = _s;
	}
	
	BoxCollider2D::~BoxCollider2D() {}
	
	void BoxCollider2D::_get_bounding_box(cg::physics::Rect2D &r) {
		if (rotation == 0) {
			r.position = position + game_object->position.get<VEC_XY>();
			r.size = rect.size;
			r.rotation = 0;
		}
		else {
			f32 max_x = max(rect[0].x, max(rect[1].x, max(rect[2].x, rect[3].x))),
				min_x = min(rect[0].x, min(rect[1].x, min(rect[2].x, rect[3].x))),
					max_y = max(rect[0].y, max(rect[1].y, max(rect[2].y, rect[3].y))),
				min_y = min(rect[0].y, min(rect[1].y, min(rect[2].y, rect[3].y)));
			
			r.size = {max_x - min_x, max_y - min_y};
			r.position = Vec2<f32>(min_x, min_y) + (r.size / 2);
			r.rotation = 0;
		}
	}
	
	bool BoxCollider2D::collide(BoxCollider2D *box) {
		rotation = game_object->rotation.z;
		rect.rotation = rotation;
		rect.position = game_object->position.get<VEC_XY>() + position.rot(rotation);
		rect.size = size;
		
		box->rotation = box->game_object->rotation.z;
		box->rect.rotation = box->rotation;
		box->rect.position = box->game_object->position.get<VEC_XY>() + box->position.rot(box->rotation);
		box->rect.size = size;
		
		cg::physics::Rect2D r1, r2;
		
		_get_bounding_box(r1);
		box->_get_bounding_box(r2);
		
		return r1.collide(r2) && rect.collide(box->rect);
	}
	
	void BoxCollider2D::debug()  {
		rotation = game_object->rotation.z;
		rect.rotation = rotation;
		rect.position = game_object->position.get<VEC_XY>() + position.rot(rotation);
		rect.size = size;
		
		cg::debug::polygon({.1, .1, 1}, {
			rect[0], rect[1], rect[2], rect[3]
		}, true);
		
		cg::physics::Rect2D r;
		_get_bounding_box(r);
		
		cg::debug::polygon({1, 1, 1}, {
			r.get(0), r.get(1), r.get(2), r.get(3)
		}, true);
	}
}