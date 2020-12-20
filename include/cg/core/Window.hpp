#ifndef CG_CORE_WINDOW_H
#define CG_CORE_WINDOW_H

#include <iostream>
#include <SDL2/SDL.h>

#include "../math.hpp"
#include "../Timer.hpp"
#include "../input.hpp"
#include "../key_code.hpp"

using namespace cg::math;

namespace cg {
	namespace core {
		enum class Mouse {
			LEFT = 0,
			MIDDLE = 1,
			RIGHT = 2,
			X1 = 3,
			X2 = 4
		};

		class WindowManager;

		class Window {
		public:
			Uint32 id;
			f32 life_time;
			f32 delta_time;
			Vec4<f32> color;
			Vec2<i32> size;
			
			Window(std::string title, Vec2<i32> res);
			~Window();
			
			i32 fps();
			
			bool key_up(cg::key_code key);
			bool key_down(cg::key_code key);
			bool key_press(cg::key_code key);
			
			bool mouse_down(Mouse button);
			bool mouse_press(Mouse button);
			bool mouse_up(Mouse button);
			
			Vec2<i32> mouse_pos();
			Vec2<i32> mouse_rel();
			Vec2<i32> mouse_wheel();
			
			void title(std::string title);
			
			void viewport(i32 x, i32 y, i32 width, i32 height);
			void ortho2d();
			void clear();
			void depth_test(bool enable);
			
			bool update();
			void quit();
			void log(std::string);
		
		private:
			friend class WindowManager;
			
			SDL_Window* _window;
			SDL_GLContext _context;

			u32 _window_id;

			bool *_key_up;
			bool *_key_down;
			bool *_key_press;
			
			struct {
				Vec2<i32> pos;
				Vec2<i32> rel;
				Vec2<i32> wheel;
				bool* btn_down;
				bool* btn_press;
				bool* btn_up;
			} _mouse;
			
			cg::time::Timer _timer;
			cg::time::Timer _lifetimer;
			
			bool _closed;
			f32 fps_avg;
			f32 fps_count;
		};
	}
}

#endif // CG_CORE_WINDOW_H