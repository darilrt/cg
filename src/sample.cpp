#include "cg/cg.hpp"

class SampleScene : public cg::Scene {
public:
	void start() {
	}
	
	void update() {
	}
	
private:
};

i32 main(i32 argc, i8* argv[]) {
	cg::display::init(Vec2<i32>(800, 600));
	cg::display::title("CG Sample");
	
	cg::run(new SampleScene());
	return 0;
}