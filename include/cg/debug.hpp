#ifndef CG_DEBUG_H
#define CG_DEBUG_H

#include "math.hpp"

#include <iostream>
#include <chrono>
#include <vector>

using namespace cg::math;

namespace cg {
	namespace debug {
		void point(Vec3<float> color, Vec2<float> position);
		void line(Vec3<float> color, Vec2<float> start, Vec2<float> end);
		void rect(Vec3<float> color, Vec2<float> position, Vec2<float> size, bool stroke=false);
		void points(Vec3<float> color, std::vector<Vec2<float>> points);
		void polygon(Vec3<float> color, std::vector<Vec2<float>> points, bool stroke=false);
		void circle(Vec3<float> color, Vec2<float> position, float radius, u32 steps=360, bool stroke=false);
	}

	inline std::string _to_string(std::string v) {return v;}

	inline std::string _to_string(char v) {return std::string(1, v);}
	inline std::string _to_string(char* v) {return v;}
	inline std::string _to_string(const char* v) {return v;}
	inline std::string _to_string(short v) {return std::to_string(v);}
	inline std::string _to_string(int v) {return std::to_string(v);}
	inline std::string _to_string(long int v) {return std::to_string(v);}
	inline std::string _to_string(long long int v) {return std::to_string(v);}

	inline std::string _to_string(unsigned char v) {return std::to_string(v);}
	inline std::string _to_string(unsigned short v) {return std::to_string(v);}
	inline std::string _to_string(unsigned int v) {return std::to_string(v);}
	inline std::string _to_string(unsigned long int v) {return std::to_string(v);}
	inline std::string _to_string(unsigned long long int v) {return std::to_string(v);}

	inline std::string _to_string(float v) {return std::to_string(v);}
	inline std::string _to_string(double v) {return std::to_string(v);}

	inline std::string _to_string(bool v) {return std::to_string(v);}

	template<typename T> 
	inline std::string _to_string(Vec2<T> v) {return v.to_string();}

	template<typename T> 
	inline std::string _to_string(Vec3<T> v) {return v.to_string();}

	template<typename T> 
	inline std::string _to_string(Vec4<T> v) {return v.to_string();}

	template<typename T> 
	inline std::string _to_string(T o) {return o.to_string();}

	inline void print() {}

	template<typename T>
	void print(T t) {
		std::cout << _to_string(t);
	}

	template<typename T, typename... A>
	void print(T t, A... a) {
		print(t);
		std::cout << " ";
		print(a...);
	}

	template<typename... A>
	void log(A... a) {
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);

		std::cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " - ";
		print(a..., "\n");
	}
}

#endif // CG_DEBUG_H