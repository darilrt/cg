#include "cg/cg.hpp"

class SampleScene : public cg::Scene {
public:	
	void start() {
		canvas = cg::instantiate<cg::gui::Canvas>();
	}
	
	void update() {
	}
	
	void render() {
	}
	
private:
	cg::gui::Canvas *canvas;
};

i32 main(i32 argc, i8* argv[]) {
	cg::display::init(Vec2<i32>(800, 600));
	cg::display::title("CG Sample");
	cg::display::icon("assets/icon.png");
	
	cg::run(new SampleScene());
	return 0;
}