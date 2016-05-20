#include "Texture.h"

#include <SDL_image.h>
#include <shared/Console.h>
#include <shared/System.h>
#include <client/components/Graphics.h>

Texture::Texture() {}
Texture::Texture(const Texture &second) { operator=(second); }
Texture &Texture::operator=(const Texture &second) {
	data = second.data;
	aspect = second.aspect;
	flags = second.flags;
	return *this;
}
Texture::Texture(const GLvoid *pixels, int w, int h, int fl) {
	data = TextureDataPtr();
	aspect = 1.0f * w / h;
	flags = fl;
	Bind();
	int anisotropyI;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropyI);
	if (flags & TEXTURE_ANISOTROPY)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyI);
	if (flags & TEXTURE_FILTERING) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (flags & TEXTURE_DEPTH)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0,
		             GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		             pixels);
}
Texture::Texture(std::string filepath, int fl) {
	std::string path = g_System()->GetDataFile(filepath);
	SDL_Surface *temp;
	if ((temp = IMG_Load(path.c_str())) == NULL) {
		g_Console()->Err("Error Loading Texture: " + filepath + " : " +
		                 std::string(IMG_GetError()));
		return;
	}
	SDL_Surface *converted = g_Graphics()->to_RGBA(temp);
	SDL_FreeSurface(temp);

	if (converted == NULL) {
		g_Console()->Err("Error Loading Texture: " + filepath + " : " +
		                 std::string(SDL_GetError()));
		SDL_FreeSurface(converted);
		return;
	}
	GLint maxTexSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if (converted->w > maxTexSize) {
		g_Console()->Err("Error Loading Texture: " + filepath + " : " +
		                 std::string(SDL_GetError()));
		SDL_FreeSurface(converted);
		return;
	}
	data = TextureDataPtr();
	aspect = 1.0f * converted->w / converted->h;
	flags = fl;
	Bind();
	int anisotropyI;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropyI);
	if (flags & TEXTURE_ANISOTROPY)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyI);
	if (flags & TEXTURE_FILTERING) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (flags & TEXTURE_DEPTH)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, converted->w, converted->h,
		             0, GL_DEPTH_COMPONENT, GL_FLOAT, converted->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, converted->w, converted->h, 0,
		             GL_RGBA, GL_UNSIGNED_BYTE, converted->pixels);

	SDL_FreeSurface(converted);
	g_Console()->Info("Texture loaded " + filepath);
}
Texture::~Texture() { data.reset(); }
void Texture::Bind() const {
	if (data)
		glBindTexture(GL_TEXTURE_2D, *data);
}
Texture::Data::Data() {
	glGenTextures(1, &id);
	if (id)
		glActiveTexture(GL_TEXTURE0);
}
Texture::Data::~Data() {
	if (id)
		glDeleteTextures(1, &id);
}
