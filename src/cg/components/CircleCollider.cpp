#include "cg/components/CircleCollider.hpp"

namespace cg {
	CircleCollider::CircleCollider(bool s) {
		position = {0, 0};
		radius = 0;
		is_static = s;
	}
	
	CircleCollider::CircleCollider(const Vec2<f32> p, const f32 r, bool s) {
		position = p;
		radius = r;
		is_static = s;
	}
	
	void CircleCollider::_get_bounding_box(cg::physics::Rect2D &r) {
		r.size = {radius * 2, radius * 2};
		r.position = position;
		r.rotation = 0;
	}
	
	void CircleCollider::debug()  {
		circle.radius = radius;
		circle.position = game_object->position.get<VEC_XY>() + position.rot(game_object->rotation.z);
		
		cg::debug::circle({.1, .1, 1}, circle.position, circle.radius, 360, true);
		
		cg::physics::Rect2D r;
		_get_bounding_box(r);
		
		cg::debug::polygon({1, 1, 1}, {
			r.get(0), r.get(1), r.get(2), r.get(3)
		}, true);
	}
}