#include <iostream>
#include <vector>
#include <GL/gl.h>

#include "cg/debug.hpp"

namespace cg {
	namespace debug {
		void point(Vec3<float> color, Vec2<float> point) {
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_POINTS);
			glColor3f(color.x, color.y, color.z);
			glVertex2f(point.x, point.y);
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
		
		void line(Vec3<float> color, Vec2<float> start, Vec2<float> end) {
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINES);
			glColor3f(color.x, color.y, color.z);
			glVertex2f(start.x, start.y);
			glVertex2f(end.x, end.y);
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
		
		void rect(Vec3<float> color, Vec2<float> pos, Vec2<float> size, bool stroke) {
			glDisable(GL_TEXTURE_2D);
			glBegin(stroke ? GL_LINE_LOOP : GL_POLYGON);
			glColor3f(color.x, color.y, color.z);
			glVertex2f(pos.x, pos.y);
			glVertex2f(pos.x, pos.y + size.y);
			glVertex2f(pos.x + size.x, pos.y + size.y);
			glVertex2f(pos.x + size.x, pos.y);
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
		
		void points(Vec3<float> color, std::vector<Vec2<float>> points) {
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_POINTS);
			glColor3f(color.x, color.y, color.z);
			
			for(Vec2<float> point : points) {
				glVertex2f(point.x, point.y);
			}
			
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
		
		void polygon(Vec3<float> color, std::vector<Vec2<float>> points, bool stroke) {
			glDisable(GL_TEXTURE_2D);
			glBegin(stroke ? GL_LINE_LOOP : GL_POLYGON);
			glColor3f(color.x, color.y, color.z);
			
			for(Vec2<float> point : points) {
				glVertex2f(point.x, point.y);
			}
			
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
		
		void circle(Vec3<float> color, Vec2<float> position, float radius, u32 steps, bool stroke) {
			std::vector<Vec2<f32>> points;
			for (int i=0; i < 360; i += 360 / steps) {
				points.push_back(Vec2<f32>(radius, 0).rot(i) + position);
			}
			
			polygon(color, points, stroke);
		}
	}
}