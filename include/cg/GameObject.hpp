#ifndef CG_GAMEOBJECT_H
#define CG_GAMEOBJECT_H

#include "math.hpp"
#include "Component.hpp"

#include <vector>

using namespace cg::math;

namespace cg {
	class Scene;
	
	class GameObject {
	public:
		Scene *scene;
		Vec3<f32> position = {0, 0, 0},
				  rotation = {0, 0, 0},
				  scale = {1, 1, 1};
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
	
		void regist(Component*);
		
		~GameObject();
	
	private:
		std::vector<Component*> components;
		
		friend void run(Scene*);
	};
}

#endif // CG_GAMEOBJECT_H