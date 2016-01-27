#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include <string>
#include <map>
#include "../../../../other/sdl/include/SDL_ttf.h"
#include "../../../tools/quad2.h"
#include "../../../tools/quad3.h"
#include "../../../tools/Protocol.h"
#include "../../../../other/glew/include/glew.h"
#define GLM_FORCE_RADIANS
#include "../../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Graphics;
class Model;
class Texture;

class Resources{
public:
	Resources(){};

	///<summary>Loads all the objects from data folder</summary>
	void Load();
	///<summary>UnLoads all the objects from data folder</summary>
	void UnLoad();
	///<summary>UnLoads all the objects from buffers</summary>
	void ClearBuffers();

	//textures
public:
	///<summary>Quades for the 8x8-tile texture</summary>
	vector<quad2> texturePos8;
	///<summary>Quades for the 8x4-tile texture</summary>
	vector<quad2> texturePos8x4;
	///<summary>Quades for the 16x16-tile texture</summary>
	vector<quad2> texturePos16;
	///<summary>Quades for the 16x8-tile texture</summary>
	vector<quad2> texturePos16x8;
	///<summary>Skin textures</summary>
	map<string, Texture*> skinTextures;
	///<summary>White 1px texture</summary>
	Texture* textureBlank;
	///<summary>RGB texture</summary>
	Texture* textureRGB;
	///<summary>InGame HUD texture</summary>
	Texture* textureGame;
	///<summary>Shadow texture(Depth)</summary>
	Texture* textureShadowDepth;
	///<summary>InGame cursor quads</summary>
	vector<quad2> gameCursor;

	//models
public:
	///<summary>Weapon models</summary>
	vector<Model*> weaponModels;
	///<summary>3-axis coords model</summary>
	class Model* coordsModel;
private:
	///<summary>Filenames of weapon OBJs</summary>
	static const char* weaponFiles[NUM_WEAPONS];
	///<summary>Filenames of weapon PNGs</summary>
	static const char* weaponTextureFiles[NUM_WEAPONS];

	//shaders
public:
	///<summary>Loads shader from the file</summary>
	///<param name="filepath">File name in data directory</param>
	///<param name="shader">Shader id</param>
	///<returns>true if all right, false if error found</returns>
	bool LoadShader(const string& filepath, GLuint &shader);
	///<summary>UnLoads shader</summary>
	///<param name="shader">Shader id</param>
	void UnLoadShader(GLuint &shader);
	///<summary>3d shader</summary>
	GLuint shader3d;
	///<summary>Shadow shader</summary>
	GLuint shaderShadow;
	///<summary>2d shader</summary>
	GLuint shader2d;

	//text
public:
	///<summary>Get font</summary>
	///<param name="size">Text size</param>
	TTF_Font* LoadFont(int size);
private:
	///<summary>Font name</summary>
	static const std::string fontName;
	///<summary>Font path</summary>
	std::string fontPath;
	///<summary>Fonts</summary>
	std::map<int, TTF_Font*> fonts;

	//colors
public:
	///<summary>White for sdl</summary>
	static const SDL_Color SDLColorWhite;
	///<summary>Black for sdl</summary>
	static const SDL_Color SDLColorBlack;
};

#endif