#include "cg/cg.hpp"

class Player : public cg::GameObject {
public:
	cg::Camera *camera;
	
	Player() {
		transform = Transform();
	}
	
	void update() {
		camera->transform.position = this.position;
	}

private:
	cg::Transform transform;
}

class Scene : public cg::Scene {
public:
	Scene() {
		regist(player);
	}
	
	void update() {
		
	}
	
private:
	cg::Camera camera;
	Player player;
}

int main() {
	cg::display::show({800, 600});
	cg::display::set_title("Test");
	cg::scene_manager::load<Scene>();
	return 0;
}