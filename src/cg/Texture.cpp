
#include "cg/Texture.hpp"

#include <string>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace cg {
	Texture::Texture() {}
	
	Texture::~Texture() {
		glDeleteTextures(1, &texture);
	}

	Texture::Texture(const std::string file_path) {
		GLuint tex;
		GLuint format;

		SDL_Surface* image = IMG_Load(file_path.c_str());
		
		if (image == NULL)
			printf("SDL_Error: %s\n", SDL_GetError());

		if (image->format->BytesPerPixel == 4)
			if (image->format->Bmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_RGBA;

		else if (image->format->BytesPerPixel == 3)
			if (image->format->Bmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_RGB;

		else
			printf("warning: the image is not truecolor..  this will probably break %i\n", image->format->BytesPerPixel);

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, image->format->BytesPerPixel, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);

		this->texture = tex;
		this->size.x = image->w;
		this->size.y = image->h;
	}

	Texture* Texture::load(const std::string file_path) {
		return new Texture(file_path);
	}
}