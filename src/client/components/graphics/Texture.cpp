#include "Texture.h"
#include "../Graphics.h"
#include "../../../shared/System.h"
#include "../../../shared/Console.h"

void Texture::Initialize(std::string filepath, bool anisotropy, bool filtering) {
	string path = g_System()->GetDataFile(filepath);
	SDL_Surface *temp = NULL;
	temp = IMG_Load(path.c_str());
	Initialize(temp, anisotropy, filtering);
	if (id==0) {
		Console::Err("Error Loading Texture: " + filepath + " : " + string(SDL_GetError()));
		SDL_FreeSurface(temp);
		return;
	}
	SDL_FreeSurface(temp);
	Console::Info("Texture loaded " + filepath);
};
void Texture::Initialize(SDL_Surface* &data, bool anisotropy, bool filtering) {
	g_Graphics()->to_RGBA(data);
	GLint maxTexSize;
	if (data == NULL) {
		id = 0;
		return;
	}
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if (data->w > maxTexSize) {
		id = 0;
		return;
	}
	Initialize(data->pixels, anisotropy, filtering, data->w, data->h);
};
void Texture::Initialize(const GLvoid* pixels, bool anisotropy, bool filtering, int w, int h, bool isDepth) {
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glEnable(GL_TEXTURE_2D);
	int anisotropyI;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropyI);
	if (anisotropy)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyI);//TODO anisotropy filterring
	if (!filtering) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (isDepth) glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	aspect = 1.0f*w / h;
	cleanup = true;
};
Texture::~Texture() {
	if(cleanup)
		glDeleteTextures(1, &id);
};
void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
};
