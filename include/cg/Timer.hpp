#ifndef CG_TIME_TIMER_H
#define CG_TIME_TIMER_H

#include <chrono>

namespace cg {
	namespace time {
		class Timer {
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> start;
			
		public:
			Timer();
			void restart();
			float current();
		};
	}
}

#endif // CG_TIME_TIMER_H