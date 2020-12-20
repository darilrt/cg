#ifndef CG_CIRCLE_COLLIDER_H
#define CG_CIRCLE_COLLIDER_H

#include "../math.hpp"
#include "../physics.hpp"
#include "../debug.hpp"
#include "../Collider.hpp"
#include "../GameObject.hpp"

namespace cg {
	class CircleCollider : public Collider {
	public:
		Vec2<f32> position;
		f32 radius;
		
		void debug();
		
		CircleCollider(bool is_static=false);
		CircleCollider(const Vec2<f32> position, const f32 radius, bool is_static=false);
		
	private:
		cg::physics::Circle circle;
		
		void _get_bounding_box(cg::physics::Rect2D &r);
	};
}

#endif // CG_CIRCLE_COLLIDER_H