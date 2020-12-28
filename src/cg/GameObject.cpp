#include "cg/Scene.hpp"
#include "cg/GameObject.hpp"
#include "cg/Component.hpp"

namespace cg {
	void GameObject::regist(cg::GameObject* object) {
		object->parent = this;
		scene->regist(object);
	}
	
	void GameObject::regist(cg::Component* component) {
		component->game_object = this;
		components.push_back(component);
	}
	
	GameObject::~GameObject() {
		for (cg::Component* p : components) {
			delete p;
		}
		
		components.clear();
	}
	
	Vec3<f32> GameObject::world_position() {
		if (parent != nullptr) {
			return parent->position + (position.rot(parent->rotation));
		}
		
		return position;
	}
}
