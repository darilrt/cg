#ifndef CG_GAMEOBJECT_H
#define CG_GAMEOBJECT_H

#include "math.hpp"
#include "debug.hpp"

#include <vector>

using namespace cg::math;

namespace cg {
	class Component;
	class Scene;
	
	class GameObject {
	public:
		GameObject *parent = nullptr;
		Scene *scene;
		
		Vec3<f32> position = {0, 0, 0},
				  rotation = {0, 0, 0},
				  scale = {1, 1, 1};
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
		
		void regist(GameObject*);
		void regist(Component*);
		
		Vec3<f32> world_position();
		
		~GameObject();
	
	private:
		std::vector<Component*> components;
		
		friend void run(Scene*);
	};
}

#endif // CG_GAMEOBJECT_H