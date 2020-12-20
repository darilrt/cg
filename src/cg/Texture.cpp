#include <string>
#include <GL/gl.h>

#include "cg/math.hpp"
#include "cg/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb_image.h>

using namespace cg::math;

namespace cg {
	Texture::Texture() {}
	
	Texture::~Texture() {
		glDeleteTextures(1, &texture);
	}

	Texture::Texture(const std::string file_path) {
		GLuint tex;
		GLuint format;
		
		int w, h, n;
		u8 *image = stbi_load(&file_path[0], &w, &h, &n, 0);
		
		if (image == nullptr) {
			printf("stbi_load error on load image");
			return;
		}
		
		switch (n) {
			case 1: /* format = GL_GRAY; */ break;
			case 2: /* format = GL_GRAY; */ break;
			case 3: format = GL_RGB; break;
			case 4: format = GL_RGBA; break;
		}

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, n, w, h, 0, format, GL_UNSIGNED_BYTE, image);

		glBindTexture(GL_TEXTURE_2D, 0);
		
		delete image;

		this->texture = tex;
		this->size.x = w;
		this->size.y = h;
	}

	Texture* Texture::load(const std::string file_path) {
		return new Texture(file_path);
	}
}