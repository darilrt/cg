#ifndef CG_SCENE_H
#define CG_SCENE_H

#include "core/Camera.hpp"
#include "GameObject.hpp"
#include "Component.hpp"

#include <vector>

namespace cg {
	class Scene {
	public:
		cg::core::Camera2D *camera;
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
		
		void regist(GameObject*);
		void regist(Component*);
		
		Scene();
		~Scene();
		
	private:
		std::vector<GameObject*> game_objects;
		std::vector<Component*> components;
		
		friend void run(Scene*);
	};
}

#endif // CG_SCENE_H