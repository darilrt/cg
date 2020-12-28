#ifndef CG_BOX_COLLIDER_2D_H
#define CG_BOX_COLLIDER_2D_H

#include "../math.hpp"
#include "../physics.hpp"
#include "../debug.hpp"
#include "../Collider.hpp"
#include "../GameObject.hpp"

namespace cg {
	class BoxCollider2D : public Collider {
	public:
		Vec2<f32> position, size;
		f32 rotation;
		
		void debug();
		
		BoxCollider2D(bool is_static=false);
		BoxCollider2D(const Vec2<f32> position, const Vec2<f32> size, bool is_static=false);
		~BoxCollider2D();
		
		bool collide(BoxCollider2D *box);
		
		void _get_bounding_box(cg::physics::Rect2D &r);
		
	private:
		cg::physics::Rect2D rect;
	};
}

#endif // CG_BOX_COLLIDER_2D_H