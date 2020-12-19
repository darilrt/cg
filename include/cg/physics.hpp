#ifndef CG_PHYSICS_H
#define CG_PHYSICS_H

#include <tuple>

#include "math.hpp"

using namespace cg::math;

namespace cg {
	namespace physics {
		class Ray2D {
		public:
			Vec2<f32> position,
					  direction;
			
			Ray2D();
			Ray2D(const Vec2<f32> position, const Vec2<f32> direction);
			
			std::pair<bool, f32> intersect(const Ray2D &ray);
			
		private:
		};
		
		class Rect2D {
		public:
			Vec2<f32> position,
					  size;
					  
			f32 rotation = 0;
			
			Rect2D();
			bool collide(Rect2D &rect);
			bool collide(Vec2<f32> &p);
			
			Vec2<f32> get(u8 point);
			
			inline Vec2<f32> operator [](u8 index) {return get(index);}
			
		private:
			bool _collide_in_axis_sat(Vec2<f32>& axis, cg::physics::Rect2D& r);
			bool _collide_in_axis_sat(Vec2<f32>& axis, Vec2<f32>& p);
		};
	}
}

#endif // CG_PHYSICS_H