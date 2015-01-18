#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include <map>
#include <string>
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

class Resources{
public:
	///<summary>Link to the Graphics component</summary>
	class Graphics* m_Graphics;
	///<summary>Stores 'g' to the 'm_Graphics'</summary>
	///<param name="g">Link to the Graphics component</param>
	Resources(Graphics* g){m_Graphics=g;};

	//textures

	///<summary>Loads texture from the file</summary>
	///<param name="filepath">File name in data directory</param>
	///<param name="tex">Texture id</param>
	///<param name="mipmaps">Use mipmaps?</param>
	///<param name="filtering">Use filtering?</param>
	///<returns>true if all right, false if error found</returns>
	bool loadTexture(string filepath, GLuint &tex,bool mipmaps,bool filtering);
	///<summary>Loads texture from the SDL_Surface</summary>
	///<param name="data">SDL_Surface</param>
	///<param name="tex">Texture id</param>
	///<param name="mipmaps">Use mipmaps?</param>
	///<param name="filtering">Use filtering?</param>
	///<returns>true if all right, false if error found</returns>
	bool loadTextureFromSurface(SDL_Surface* &data, GLuint &tex,bool mipmaps,bool filtering);
	///<summary>UnLoads texture</summary>
	///<param name="tex">Texture id</param>
	void unLoadTexture(GLuint &tex);
	///<summary>Quades for the 8x8-tile texture</summary>
	vector<quad2> texturePos8;
	///<summary>Quades for the 8x4-tile texture</summary>
	vector<quad2> texturePos8x4;
	///<summary>Quades for the 16x16-tile texture</summary>
	vector<quad2> texturePos16;
	///<summary>Quades for the 16x8-tile texture</summary>
	vector<quad2> texturePos16x8;
	///<summary>Skin textures</summary>
	map<string,GLuint> skinTextures;
	///<summary>White 1px texture</summary>
	GLuint textureBlank;
	///<summary>RGB texture</summary>
	GLuint textureRGB;
	///<summary>InGame HUD texture</summary>
	GLuint textureGame;
	///<summary>InGame cursor quads</summary>
	vector<quad2> gameCursor;

	//models

	///<summary>Filenames of weapon OBJs</summary>
	static const char* weaponFiles[NUM_WEAPONS];
	///<summary>Filenames of weapon PNGs</summary>
	static const char* weaponTextureFiles[NUM_WEAPONS];
	///<summary>Weapon models</summary>
	vector<Model*> weaponModels;
	///<summary>3-axis coords model</summary>
	class Model* coordsModel;

	//shaders

	///<summary>Loads shader from the file</summary>
	///<param name="filepath">File name in data directory</param>
	///<param name="shader">Shader id</param>
	///<returns>true if all right, false if error found</returns>
	bool loadShader(string filepath, GLuint &shader);
	///<summary>UnLoads shader</summary>
	///<param name="shader">Shader id</param>
	void unLoadShader(GLuint &shader);
	///<summary>3d shader</summary>
	GLuint shader3d;
	///<summary>2d shader</summary>
	GLuint shader2d;

	//fonts
	///<summary>Font name</summary>
	static const string fontName;
	///<summary>Font path</summary>
	string fontPath;
	///<summary>Font sizes</summary>
	enum{
		FONT_NORMAL=1,
		FONT_BIG=2,
		FONT_DIVIDER=20,
	};
	///<summary>Fonts</summary>
	map<int,TTF_Font*> fonts;
	map<int,map<string,GLuint>> stringBuffer;
	map<int,map<string,float>> aspectBuffer;
	///<summary>Get font</summary>
	///<param name="size">Text size</param>
	TTF_Font* loadFont(int size);
	///<summary>Get text texture</summary>
	///<param name="tex">Where store texture</param>
	///<param name="aspect">Where store aspect</param>
	///<param name="data">Text</param>
	///<param name="size">Text size</param>
	bool loadStringTexture(GLuint& tex,float &aspect,string data,int size,bool buffering);

	//colors
	///<summary>White for sdl</summary>
	static const SDL_Color SDLColorWhite;
	///<summary>Black for sdl</summary>
	static const SDL_Color SDLColorBlack;

	///<summary>Loads all the objects from data folder</summary>
	void Load();
	///<summary>UnLoads all the objects from data folder</summary>
	void UnLoad();
	///<summary>UnLoads all the objects from buffers</summary>
	void ClearBuffers();
};

#endif
