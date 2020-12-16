#include "cg/Scene.hpp"

namespace cg {
	void GameObject::regist(cg::Component* component) {
		component->game_object = this;
		components.push_back(component);
	}
	
	GameObject::~GameObject() {
		for (auto p : components)
			delete p;
		
		components.clear();
	}
}
