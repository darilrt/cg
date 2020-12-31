#include "cg/cg.hpp"

cg::Scene *cg::scene = nullptr;

void cg::run(cg::Scene *scene) {
	cg::scene = scene;
	
	// Check window was intialized ---------------------
	if (cg::display::window == nullptr) {
		cg::display::init({800, 600});
	}
	
	// ======================== CREATE RENDER QUAD =========================
	
	cg::core::Shader *shader = nullptr;
	if ((shader = cg::shader::get("camera")) == nullptr) {
		shader = cg::shader::load(
			"camera",
			"assets/shaders/camera.vert",
			"assets/shaders/camera.frag"
		);
		shader->add_uniform("texture");
		shader->add_uniform("screen_resolution");
		shader->add_uniform("time");
	}
	
	cg::core::Material *material = new cg::core::Material(shader);
	material->set_uniform(
		"texture",
		new cg::core::Sampler2D(scene->camera->texture.texture)
	);
	material->set_uniform(
		"screen_resolution",
		new cg::core::Uniform2<f32>(cg::display::width, cg::display::height)
	);
	
	auto camera_time = new cg::core::Uniform1<f32>(0);
	material->set_uniform("time", camera_time);
	
	cg::core::Mesh *mesh = new cg::core::Mesh();
	
	Vec2<f32> size = cg::display::window->size;
	
	f32 &w = cg::display::width,
		&h = cg::display::height;
	
	mesh->vertex = {
		{ 0, 0, 0},
		{ 0, h, 0},
		{ w, h, 0},
		{ w, 0, 0},
	};
	
	mesh->uv = {
		{0, 0},
		{0, 1},
		{1, 1},
		{1, 0},
	};
	
	mesh->elements = {
		{2, 1, 0},
		{0, 3, 2},
	};
	
	mesh->bind();
	
	cg::core::MeshRenderer mesh_renderer(mesh, material);
	mesh_renderer.position = {-w / 2, -h / 2, 0};
	mesh_renderer.rotation = {0, 0, 0};
	mesh_renderer.scale = {1, 1, 1};
	
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
		for (cg::GameObject* obj : scene->go_wait_list) {
			obj->start();
			
			for (cg::Component* cmp : obj->components) {
				if (cmp->is_enable) cmp->start();
			}
		}
		
		scene->game_objects.insert(
			scene->game_objects.end(),
			scene->go_wait_list.begin(),
			scene->go_wait_list.end()
		);
		
		scene->go_wait_list.clear();
		
		cg::time::fps = cg::display::window->fps();
		cg::time::delta_time = cg::display::window->delta_time; // probar cambiarlo a referencia
		cg::time::life_time = cg::display::window->life_time; // probar cambiarlo a referencia
		camera_time->value = cg::time::life_time;
		
		// Update ------------------------------------------
		for (cg::GameObject* obj : scene->game_objects) {
			for (cg::Component* cmp : obj->components) {
				if (cmp->is_enable) cmp->update();
			}
			
			obj->update();
		}
		
		for (cg::Component* cmp : scene->components) {
			if (cmp->is_enable) cmp->update();
		}
		
		scene->update();
		
		// Render ------------------------------------------
		glViewport(0, 0, cg::display::window->size.x, cg::display::window->size.y);
		scene->camera->begin();
		
		for (cg::GameObject* obj : scene->game_objects) {
			for (cg::Component* cmp : obj->components) {
				cmp->render();
			}
			
			obj->render();
		}
		
		for (cg::Component* cmp : scene->components) {
			if (cmp->is_enable) cmp->render();
		}
		
		scene->render();
		scene->camera->end();
		
		cg::display::window->clear();
		mesh_renderer.render();
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