#include "Texture.h"

#include <client/components/Graphics.h>
#include <shared/System.h>

#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY
#define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84FF
#endif
#ifndef GL_TEXTURE_MAX_ANISOTROPY
#define GL_TEXTURE_MAX_ANISOTROPY 0x84FE
#endif

Texture::Texture() {}
Texture::Texture(const GLvoid *pixels, glm::uvec2 s, int fl) : flags(fl) {
	g_Graphics(); // TODO: fix
	data = make_dataPtr();
	aspect = 1.0f * s.x / s.y;
	size = s;
	SetPixels(pixels);
}
Texture::Texture(SDL_Surface *surface, int fl) : flags(fl) {
	SDL_Surface *converted = g_Graphics()->to_RGBA(surface);

	if (converted == nullptr) {
		return;
	}
	GLint maxTexSize;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if (converted->w > maxTexSize) {
		SDL_FreeSurface(converted);
		return;
	}

	data = make_dataPtr();
	aspect = 1.0f * converted->w / converted->h;
	size = glm::vec2(converted->w, converted->h);
	SetPixels(converted->pixels);

	SDL_FreeSurface(converted);
}
void Texture::SetPixels(const GLvoid *pixels) {
	Bind();
	int anisotropyI;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &anisotropyI);
	if ((flags & TEXTURE_ANISOTROPY) != 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisotropyI);
	}
	if ((flags & TEXTURE_FILTERING) != 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		                (flags & TEXTURE_MIPMAP) != 0 ? GL_LINEAR_MIPMAP_LINEAR
		                                              : GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		                (flags & TEXTURE_MIPMAP) != 0 ? GL_NEAREST_MIPMAP_NEAREST
		                                              : GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
	                (flags & TEXTURE_REPEAT) != 0 ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
	                (flags & TEXTURE_REPEAT) != 0 ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	if ((flags & TEXTURE_DEPTH) != 0) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0,
		             GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, pixels);
	} else if ((flags & TEXTURE_FLOAT) != 0) {
		glTexImage2D(GL_TEXTURE_2D, 0,
		             (flags & TEXTURE_3CORD) != 0
		                 ? GL_RGB32F
		                 : (flags & TEXTURE_1CORD) != 0 ? GL_R32F : GL_RGBA32F,
		             size.x, size.y, 0,
		             (flags & TEXTURE_3CORD) != 0
		                 ? GL_RGB
		                 : (flags & TEXTURE_1CORD) != 0 ? GL_RED : GL_RGBA,
		             GL_FLOAT, pixels);
	} else {
		glTexImage2D(
		    GL_TEXTURE_2D, 0, (flags & TEXTURE_3CORD) != 0
		                          ? GL_RGB
		                          : (flags & TEXTURE_1CORD) != 0 ? GL_RED : GL_RGBA,
		    size.x, size.y, 0, (flags & TEXTURE_3CORD) != 0
		                           ? GL_RGB
		                           : (flags & TEXTURE_1CORD) != 0 ? GL_RED : GL_RGBA,
		    GL_UNSIGNED_BYTE, pixels);
	}
	if ((flags & TEXTURE_MIPMAP) != 0) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
void Texture::Bind() const {
	if (data) {
		glBindTexture(GL_TEXTURE_2D, *data);
	}
}
Texture::Data::Data() {
	glGenTextures(1, &id);
	if (id != 0u) {
		glActiveTexture(GL_TEXTURE0);
	}
}
Texture::Data::~Data() {
	if (id != 0u) {
		glDeleteTextures(1, &id);
	}
}
