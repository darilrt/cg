#include "cg/cg.hpp"
using namespace cg::math;

class PhysicsScene : public cg::Scene {
public:
	void start() {
		
	}
	
	void update() {
		cg::display::title(std::to_string(cg::time::fps));
	}
	
private:
	
};

// int main(i32 argc, i8* argv[]) {
	// cg::display::init({800, 600});
	// cg::run(new PhysicsScene());
	
	// return 0;
// }