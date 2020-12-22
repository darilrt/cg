#include "cg/cg.hpp"

cg::Scene *cg::scene = nullptr;

void cg::run(cg::Scene *scene) {
	cg::scene = scene;
	
	// Check window was intialized ---------------------
	if (cg::display::window == nullptr) {
		cg::display::init({800, 600});
	}
	
	// Start -------------------------------------------
	scene->start();
	for (cg::GameObject* obj : scene->game_objects) {
		obj->start();
		
		for (cg::Component* cmp : obj->components) {
			if (cmp->is_enable) cmp->start();
		}
	}
	
	for (cg::Component* cmp : scene->components) {
		if (cmp->is_enable) cmp->start();
	}
	
	while (cg::display::window->update()) {
		cg::time::fps = cg::display::window->fps();
		cg::time::delta_time = cg::display::window->delta_time; // probar cambiarlo a referencia
		cg::time::life_time = cg::display::window->life_time; // probar cambiarlo a referencia
		
		// Update ------------------------------------------
		scene->update();
		for (cg::GameObject* obj : scene->game_objects) {
			obj->update();
			
			for (cg::Component* cmp : obj->components) {
				if (cmp->is_enable) cmp->update();
			}
		}
		
		for (cg::Component* cmp : scene->components) {
			if (cmp->is_enable) cmp->update();
		}
		
		// Render ------------------------------------------
		cg::display::window->clear();
		
		scene->camera->use();
		scene->render();
		
		for (cg::GameObject* obj : scene->game_objects) {
			obj->render();
			
			for (cg::Component* cmp : obj->components) {
				cmp->render();
			}
		}
		
		for (cg::Component* cmp : scene->components) {
			if (cmp->is_enable) cmp->render();
		}
	}
}

void cg::destroy(GameObject *go) {
	scene->game_objects.erase(
		std::remove_if(scene->game_objects.begin(), scene->game_objects.end(),
			[&go](GameObject* e) {
				return e == go;
			}),
		scene->game_objects.end());
	
	delete go;
}