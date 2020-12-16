// Cagada de Engine (CG) beta v0.0.9
#include "cg/cg.hpp"
#include "cmath"

// class Collider : public cg::Component {
// public:
	// void start() {
		
	// }
	
	// void update() {
	// }
	
	// void render() {
	// }

// private:
	
// }

class Planet : public cg::GameObject {
public:
	void start() {
		regist(particles = new cg::ParticleEmitter());
		particles->max = 1000;
		particles->rate = 10000;
		particles->is_global = true;
		particles->is_emitting = true;
		
		particles->spawn_func = [this](cg::core::Particle &p) {
			p.max_life_time = 5;
			
			f32 d = cg::random(100, 150);
			p.position = position +
				Vec3<f32>(d, 0, 0).rot({0, 0, cg::random(0, 360)})
			;
			p.position.z = 0.5;
			
			Vec3<f32> dir = (position - p.position);
			p.speed = Vec3<f32>(dir.y, dir.x * -1, 0).unlit() * sqrt(100 / d) * 100;
			p.size = cg::random(2, 5);
			
			p.color = {.8, .8, .8, 1};
		};
		
		particles->update_func = [this](cg::core::Particle &p) {
			Vec3<f32> dir = (position - p.position);
			f32 d = dir.length() / 100;
			
			dir = dir.unlit();
			
			p.speed += dir * (100 / (d*d)) * cg::time::delta_time;
			p.position += p.speed * cg::time::delta_time;
			p.position.z = 0.5;
			
			p.rotation += 180 * cg::time::delta_time * TO_RADIANS;
			
			p.life_time = 0;
		};
		
		regist(sprite = new cg::Sprite("assets/planet.png"));
		sprite->scale = {3, 3, 0};
		
		position.z = 0;
	}
	
	void update() {
	}

private:
	cg::Sprite *sprite;
	cg::ParticleEmitter *particles;
};

class Player : public cg::GameObject {
public:
	Vec3<f32> direction = {0, 0, 0};
	f32 speed = 1000;
	
	void start() {
		regist(particles = new cg::ParticleEmitter());
		particles->rate = 1000;
		particles->is_global = true;
		
		particles->spawn_func = [this](cg::core::Particle &p) {
			p.max_life_time = 5;
			
			p.position = this->position + Vec3<f32>(this->direction.y, this->direction.x, 0) * cg::random(-3, 3, .1);
			p.position.z = 0.5;
			
			p.speed = direction * -1;
			p.size = cg::random(5, 8);
			
			p.color = {0, 0, 0, 1};
		};
		
		particles->update_func = [this](cg::core::Particle &p) {
			p.position += p.speed;
			p.size -= 40 * cg::time::delta_time;
			p.rotation += 720 * cg::time::delta_time * TO_RADIANS;
			
			f32 n = sin(p.life_time * 10);
			p.color = lerp(Vec4<f32>(0.4, 0.1, 0, 1), Vec4<f32>(1, 1, 0, 1), n);
			
			if (p.size <= 0)
				p.life_time = p.max_life_time;
		};
		
		regist(sprite = new cg::Sprite("assets/starship2.png"));
		sprite->scale = {3, 3, 0};
		sprite->position = {22.5, 0, 0};
		
		position.z = 1;
	}
	
	void update() {
		particles->is_emitting = cg::input::key_press(cg::key_code::W);
		
		if (particles->is_emitting) {
			auto diff = scene->camera->screen_to_world(cg::input::mouse_position()) - position.get<VEC_XY>();
			particles->is_emitting = particles->is_emitting && diff.length() > 45;
			
			if (particles->is_emitting) {
				Vec3<f32> new_dir = Vec3<f32>(diff, 0).unlit();
				direction = lerp(direction, new_dir, 10 * cg::time::delta_time).unlit();
				
				f32 l = direction.length() != 0;
				
				position += direction * speed * cg::time::delta_time;
				if (l) rotation.z = atan2(direction.y, direction.x) * TO_DEGREES;
			}
		}
	}

private:
	cg::Sprite *sprite;
	cg::ParticleEmitter *particles;
};

class CustomScene : public cg::Scene {
public:
	void start() {
		regist(stars = new cg::ParticleEmitter());
		stars->max = 200;
		stars->rate = 1000;
		stars->is_global = true;
		stars->is_emitting = true;
		
		stars->spawn_func = [this](cg::core::Particle &p) {
			p.max_life_time = 5;
			p.life_time = cg::random(0, 10);
			
			p.position = {camera->position + 
				Vec2<f32>(
					cg::random(-cg::display::width / 2, cg::display::width / 2),
					cg::random(-cg::display::height / 2, cg::display::height / 2)
			), -1};
			
			p.color = {1, 1, 1, 1};
			p.rotation = cg::random(0, 360);
		};
		
		stars->update_func = [this](cg::core::Particle &p) {
			p.rotation += 45 * cg::time::delta_time * TO_RADIANS;
			p.size = sin(p.life_time * 3) * 5;
			
			Vec2<f32> diff = p.position.get<VEC_XY>() - camera->position;
			
			if (abs(diff.x) > cg::display::width / 2)
				p.position.x = camera->position.x + sign(diff.x) * -cg::display::width / 2;
			
			if (abs(diff.y) > cg::display::height / 2)
				p.position.y = camera->position.y + sign(diff.y) * -cg::display::height / 2;
		};
		
		regist(player = new Player());
		
		regist(planet = new Planet());
	}
	
	void update() {
		camera->position = lerp(
			camera->position,
			player->position.get<VEC_XY>(),
			10 * cg::time::delta_time
		);
		
		
	}
	
	// void render() {
		// cg::debug::
	// }
	
private:
	Player *player;
	cg::ParticleEmitter *stars;
	
	Planet *planet;
};

int main(i32 argc, i8* argv[]) {
	cg::display::init({1920, 1080});
	cg::display::title("Hello, CG!");
	cg::display::background({0.05, 0.05, 0.1, 1});
	
	cg::run(new CustomScene());
	return 0;
}