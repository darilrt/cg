#include "cg/cg.hpp"

class SampleScene : public cg::Scene {
public:	
	void start() {
		camera->perspective = true;
		camera->position = {0, 0, -10};
		camera->z_near = 0.1f;
		
		r = 0;
		
		regist(pe = new cg::ParticleEmitter());
		pe->rate = 100;
		pe->is_global = true;
		pe->is_emitting = true;
		
		pe->spawn_func = [this](cg::core::Particle &p) {
			p.max_life_time = 10;
			
			p.color = {1, 1, 1, 1};
			p.speed = Vec3<f32>(0, cg::random(5, 6, 0.1), 0)
				.rot({0, 0, cg::random(-15, 15)})
				.rot({0, cg::random(-180, 180), 0});
			
			p.position = 0;
			p.rotation = 0;
			p.size = 0.1;
		};
		
		pe->update_func = [this](cg::core::Particle &p) {
			p.speed += Vec3<f32>(0, -9.86f, 0) * cg::time::delta_time;
			p.position += p.speed * cg::time::delta_time;
			p.size -= 0.08 * cg::time::delta_time;
			
			if (p.size <= 0) {
				p.life_time = 20;
			}
		};
	}
	
	void update() {
	}
	
	void render() {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		cg::debug::rect({0.1, 0.1, 0.8}, {-1, -1}, {2, 2});
		glPopMatrix();
	}
	
private:
	cg::ParticleEmitter *pe;
	
	f32 r;
};

i32 main(i32 argc, i8* argv[]) {
	cg::display::init(Vec2<i32>(800, 600));
	cg::display::title("CG Sample");
	cg::display::icon("assets/icon.png");
	
	cg::run(new SampleScene());
	return 0;
}