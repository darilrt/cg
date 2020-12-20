#ifndef CG_COMPONENT_H
#define CG_COMPONENT_H

#include "GameObject.hpp"

namespace cg {
	class Scene;
	
	class Component {
	public:
		bool is_enable = true;
		GameObject *game_object;
		Scene *scene;
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
		
	private:
	};
}

#endif // CG_COMPONENT_H