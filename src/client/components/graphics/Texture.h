#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "../../../../other/sdl/include/SDL_image.h"
#include "../../../tools/quad2.h"
#include "../../../tools/quad3.h"
#include "../../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../other/glm/gtc/type_ptr.hpp"

class Texture {
public:
	Texture() { id = 0; };
	Texture(std::string filepath, bool anisotropy, bool filtering){Initialize(filepath,anisotropy,filtering);};
	Texture(SDL_Surface* &data, bool anisotropy, bool filtering){Initialize(data,anisotropy,filtering);};
	Texture(const GLvoid* pixels, bool anisotropy, bool filtering, int w, int h, bool isDepth=false){Initialize(pixels,anisotropy,filtering,w,h,isDepth);};
	virtual ~Texture();

	void Bind();
	operator GLuint() const { return id; };
	float aspect;
protected:
    void Initialize(std::string filepath, bool anisotropy, bool filtering);
	void Initialize(SDL_Surface* &data, bool anisotropy, bool filtering);
	void Initialize(const GLvoid* pixels, bool anisotropy, bool filtering, int w, int h, bool isDepth=false);
	bool cleanup;
	GLuint id;
};

#endif
