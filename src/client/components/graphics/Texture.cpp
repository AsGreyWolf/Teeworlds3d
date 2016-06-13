#include "Texture.h"

#include <shared/System.h>
#include <client/components/Graphics.h>

Texture::Texture() {}
Texture::Texture(const Texture &second) { operator=(second); }
Texture &Texture::operator=(const Texture &second) {
	data = second.data;
	aspect = second.aspect;
	size = second.size;
	flags = second.flags;
	return *this;
}
Texture::Texture(const GLvoid *pixels, int w, int h, int fl) : flags(fl) {
	g_Graphics(); // TODO: fix
	data = TextureDataPtr();
	aspect = 1.0f * w / h;
	size = glm::vec2(w, h);
	SetPixels(pixels);
}
Texture::Texture(SDL_Surface *surface, int fl) : flags(fl) {
	SDL_Surface *converted = g_Graphics()->to_RGBA(surface);

	if (converted == NULL) {
		SDL_FreeSurface(converted);
		return;
	}
	GLint maxTexSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if (converted->w > maxTexSize) {
		SDL_FreeSurface(converted);
		return;
	}

	data = TextureDataPtr();
	aspect = 1.0f * converted->w / converted->h;
	size = glm::vec2(converted->w, converted->h);
	SetPixels(converted->pixels);

	SDL_FreeSurface(converted);
}
void Texture::SetPixels(const GLvoid *pixels) {
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0,
		             GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
		             GL_UNSIGNED_BYTE, pixels);
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
