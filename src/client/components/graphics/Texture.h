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
	///<summary>Load texture from the file</summary>
	Texture(const std::string& filepath, bool anisotropy, bool filtering){Initialize(filepath,anisotropy,filtering);};
	///<summary>Generate texture from the surface</summary>
	Texture(SDL_Surface* data, bool anisotropy, bool filtering){Initialize(data,anisotropy,filtering);};
	///<summary>Generate texture from the pixel buffer</summary>
	Texture(const GLvoid* pixels, bool anisotropy, bool filtering, int w, int h, bool isDepth=false){Initialize(pixels,anisotropy,filtering,w,h,isDepth);};
	virtual ~Texture();

	///<summary>Bind texture</summary>
	void Bind();
	operator GLuint() const { return id; };
	///<summary>W/H</summary>
	float aspect;
protected:
	///<summary>Load texture from the file</summary>
    void Initialize(const std::string& filepath, bool anisotropy, bool filtering);
	///<summary>Generate texture from the surface</summary>
	void Initialize(SDL_Surface* data, bool anisotropy, bool filtering);
	///<summary>Generate texture from the pixel buffer</summary>
	void Initialize(const GLvoid* pixels, bool anisotropy, bool filtering, int w, int h, bool isDepth=false);
	bool cleanup;
	GLuint id;
};

#endif
