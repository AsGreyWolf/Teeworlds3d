#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL_image.h>
#include <memory>
#include <string>
#define GLEW_STATIC
#ifdef __ANDROID__
#include <GLES3/gl3.h>
#else
#include <glew.h>
#endif
#include <tools/vmath.h>

enum TEXTURE_FLAGS {
	TEXTURE_DEFAULT = 0,
	TEXTURE_ANISOTROPY = 0x01,
	TEXTURE_FILTERING = 0x02,
	TEXTURE_DEPTH = 0x04,
	TEXTURE_FLOAT = 0x08,
	TEXTURE_3CORD = 0x10,
	TEXTURE_1CORD = 0x20,
	TEXTURE_REPEAT = 0x40,
	TEXTURE_MIPMAP = 0x80,
};

class Texture {
public:
	Texture(SDL_Surface *surface, int flags = TEXTURE_DEFAULT);
	Texture(const GLvoid *pixels, glm::uvec2 size, int flags = TEXTURE_DEFAULT);
	Texture();
	operator GLuint() const { return *data; };

	void Bind() const;

	float aspect = 1;
	glm::uvec2 size = glm::uvec2(0, 0);
	int flags = 0;

protected:
	void SetPixels(const GLvoid *pixels);

private:
	class Data {
	public:
		Data();
		~Data();
		operator GLuint() const { return id; };

	private:
		GLuint id = 0;
	};
	typedef std::shared_ptr<Data> TextureDataPtr;
#define TextureDataPtr(a) std::make_shared<Data>(a);

	TextureDataPtr data;
};

#endif
