#include "cg/physics.hpp"

namespace cg {
	namespace physics {
		Ray2D::Ray2D() {
			position = 0;
			direction = 0;
		}
		
		std::pair<bool, f32> Ray2D::intersect(const Ray2D &r) {
			f32 d = direction.cross(r.direction);
			
			if (d) {
				return {true, ((r.position - position).cross(r.direction)) / d};
			}
			
			return {false, 0};
		}
		
		Rect2D::Rect2D() {
			position = 0;
			size = 0;
		}
		
		bool Rect2D::collide(Rect2D &r) {
			if (rotation == 0 && r.rotation == 0) {
				return position.x < r.position.x + r.size.x &&
					   position.x + size.x > r.position.x   &&
					   position.y < r.position.y + r.size.y &&
					   position.y + size.y > r.position.y;
			}
			
			Vec2<f32> axis_r1_1(1, 0);
			axis_r1_1 = axis_r1_1.rot(this->rotation);
			Vec2<f32> axis_r1_2(axis_r1_1.y , -axis_r1_1.x);
			
			Vec2<f32> axis_r2_1(1, 0);
			axis_r2_1 = axis_r2_1.rot(r.rotation);
			Vec2<f32> axis_r2_2(axis_r2_1.y , -axis_r2_1.x);
			
			return _collide_in_axis_sat(axis_r1_1, r) &&
				   _collide_in_axis_sat(axis_r1_2, r) &&
				   _collide_in_axis_sat(axis_r2_1, r) &&
				   _collide_in_axis_sat(axis_r2_2, r);
		}
		
		bool Rect2D::collide(Vec2<f32> &p) {
			if (rotation == 0) {
				Vec2<f32> s = size / 2;
				return p.x > position.x - s.x && p.x < position.x + s.x &&
					   p.y > position.y - s.y && p.y < position.y + s.x;
			}
			
			Vec2<f32> axis_r1_1(1, 0);
			axis_r1_1 = axis_r1_1.rot(this->rotation);
			Vec2<f32> axis_r1_2(axis_r1_1.y , -axis_r1_1.x);
			
			return _collide_in_axis_sat(axis_r1_1, p) &&
				   _collide_in_axis_sat(axis_r1_2, p);
		}
		
		Vec2<f32> Rect2D::get(u8 point) {
			f32 w = size.x / 2, h = size.y / 2;
			
			switch (point) {
				case 0: return position + Vec2<f32>(-w, -h).rot(rotation);
				case 1: return position + Vec2<f32>(-w,  h).rot(rotation);
				case 2: return position + Vec2<f32>( w,  h).rot(rotation);
				case 3: return position + Vec2<f32>( w, -h).rot(rotation);
			}
			
			// throw "index out of range";
			return {0, 0}; 
		}
		
		bool Rect2D::_collide_in_axis_sat(Vec2<f32>& axis, Rect2D& r) {
			f32 r1_p1 = (this->get(0)).dot(axis),
				r1_p2 = (this->get(1)).dot(axis),
				r1_p3 = (this->get(2)).dot(axis),
				r1_p4 = (this->get(3)).dot(axis),
				r2_p1 = (r.get(0)).dot(axis),
				r2_p2 = (r.get(1)).dot(axis),
				r2_p3 = (r.get(2)).dot(axis),
				r2_p4 = (r.get(3)).dot(axis);
		
			f32 min_r1 = min(r1_p1, min(r1_p2, min(r1_p3, r1_p4))),
				max_r1 = max(r1_p1, max(r1_p2, max(r1_p3, r1_p4))),
				min_r2 = min(r2_p1, min(r2_p2, min(r2_p3, r2_p4))),
				max_r2 = max(r2_p1, max(r2_p2, max(r2_p3, r2_p4)));
			
			return !(min_r1 > max_r2) && !(max_r1 < min_r2);
		}
		
		bool Rect2D::_collide_in_axis_sat(Vec2<f32>& axis, Vec2<f32>& p) {
			f32 p1 = (this->get(0)).dot(axis),
				p2 = (this->get(1)).dot(axis),
				p3 = (this->get(2)).dot(axis),
				p4 = (this->get(3)).dot(axis);
			
			f32 min_r1 = min(p1, min(p2, min(p3, p4))),
				max_r1 = max(p1, max(p2, max(p3, p4)));
			
			f32 pp = p.dot(axis);
			return (!(min_r1 > pp)) && (!(max_r1 < pp));
		}
	}
}
