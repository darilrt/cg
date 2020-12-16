#ifndef CG_COMPONENT_H
#define CG_COMPONENT_H

namespace cg {
	class GameObject;
	class Scene;
	
	class Component {
	public:
		GameObject *game_object;
		Scene *scene;
		
		virtual void start() {};
		virtual void update() {};
		virtual void render() {};
		
	private:
	};
}

#endif // CG_COMPONENT_H