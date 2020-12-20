#include "cg/cg.hpp"

void cg::run(cg::Scene *scene) {
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