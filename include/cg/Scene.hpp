#ifndef CG_SCENE_H
#define CG_SCENE_H

#include "core/Camera.hpp"
#include "GameObject.hpp"
#include "Component.hpp"

#include <vector>
#include <list>

namespace cg {
	class Scene {
	public:
		cg::core::Camera *camera;
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
		
		void regist(GameObject*);
		void regist(Component*);
		
		Scene();
		~Scene();
		
	private:
		std::list<GameObject*> go_wait_list;
		std::list<GameObject*> game_objects;
		std::vector<Component*> components;
		
		friend void run(Scene*);
		friend void destroy(GameObject*);
	};
}

#endif // CG_SCENE_H