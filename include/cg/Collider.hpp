#ifndef CG_COLLIDE_H
#define CG_COLLIDE_H

#include "physics.hpp"
#include "Component.hpp"

namespace cg {
	class Collider : public Component {
	public:
		virtual void _get_bounding_box(cg::physics::Rect2D &r) {};
		
	protected:
		bool is_static;
	};
}

#endif // CG_COLLIDE_H