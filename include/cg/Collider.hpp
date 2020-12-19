#ifndef CG_COLLIDE_H
#define CG_COLLIDE_H

#include "physics.hpp"
#include "Component.hpp"

namespace cg {
	class Collider : public Component {
	public:
	
	private:
		virtual cg::physics::Rect2D* _get_bounding_box() {return nullptr;};
		
	protected:
		bool is_static;
	};
}

#endif // CG_COLLIDE_H