#include "Resources.h"

#include "models/Model.h"
#include "Texture.h"
#include "StringTexture.h"
#include "../Graphics.h"
#include "../../Client.h"
#include "../../../shared/Console.h"
#include "../../../shared/System.h"
#include "../../../../other/sdl/include/SDL_image.h"

const char* Resources::weaponFiles[NUM_WEAPONS]={
	"models/hammer.model",
	"models/gun.model",
	"models/shotgun.model",
	"models/grenade.model",
	"models/rifle.model",
	"models/ninja.model",
};
const char* Resources::weaponTextureFiles[NUM_WEAPONS]={
	"models/hammer.png",
	"models/gun.png",
	"models/shotgun.png",
	"models/grenade.png",
	"models/rifle.png",
	"models/ninja.png",
};
const string Resources::fontName="font.ttf";

const SDL_Color Resources::SDLColorWhite = {255, 255, 255};
const SDL_Color Resources::SDLColorBlack = {0, 0, 0};

void Resources::Load(){
	//textures
	textureBlank = new Texture("blank.png", true, false);
	textureRGB = new Texture("rgb.png", true, false);
	textureGame = new Texture("game.png", true, true);
	textureShadowDepth = new Texture(NULL,true,true, g_Graphics()->screenSize*g_Graphics()->aspect * 4, g_Graphics()->screenSize*g_Graphics()->aspect * 4, true);
	vector<string> skins;
	g_System()->GetFilesInDirectory(skins, g_System()->GetDataFile("skins"));
	for(unsigned int i=0;i<skins.size();i++){
		Texture* skintex=new Texture("skins/" + skins[i], true, false);
		skins[i].resize(skins[i].size()-4);
		skinTextures.insert(skinTextures.begin(),pair<string,Texture*>(skins[i],skintex));
	}
	for (int j = 0; j < 8; j++)for (int i = 0; i < 8;i++)
		texturePos8.push_back(quad2(1.0f*i/8,1.0f*j/8,1.0f/8,1.0f/8));
	for (int j = 0; j < 16; j++)for (int i = 0; i < 16; i++)
		texturePos16.push_back(quad2(1.0f*i / 16, 1.0f*j / 16, 1.0f / 16, 1.0f / 16));
	for (int j = 0; j < 4; j++)for (int i = 0; i< 8; i++)
		texturePos8x4.push_back(quad2(1.0f*i / 8, 1.0f*j / 4, 1.0f / 8, 1.0f / 4));
	for (int j = 0; j < 8; j++)for (int i = 0; i < 16; i++)
		texturePos16x8.push_back(quad2(1.0f*i / 16, 1.0f*j / 8, 1.0f / 16, 1.0f / 8));

	gameCursor.push_back(texturePos16x8[0]);
	gameCursor.push_back(texturePos16x8[32]);
	gameCursor.push_back(texturePos16x8[48]);
	gameCursor.push_back(texturePos16x8[64]);
	gameCursor.push_back(texturePos16x8[96]);
	gameCursor.push_back(texturePos16x8[80]);

	//models
	coordsModel=new Model(false, GL_LINES);
	coordsModel->texture=textureRGB;
	coordsModel->AddVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->AddVertex(vec3(32,0,0),vec3(0,0,1),vec2(0,0));
	coordsModel->AddVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->AddVertex(vec3(0,32,0),vec3(0,0,1),vec2(1,0));
	coordsModel->AddVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->AddVertex(vec3(0,0,32),vec3(0,0,1),vec2(0,1));
	coordsModel->Create();

	for(int i=0;i<NUM_WEAPONS;i++){
		Model* buffer;
		buffer=new Model();
		buffer->AddObjModel(weaponFiles[i]);
		buffer->Create();
		buffer->texture = new Texture(weaponTextureFiles[i], true, false);
		weaponModels.push_back(buffer);
	}

	//shaders
	LoadShader("shaders/shader",shader3d);
	LoadShader("shaders/shader2d",shader2d);
	LoadShader("shaders/shaderShadow",shaderShadow);

	//fonts
	fontPath = g_System()->GetDataFile(fontName);
}
void Resources::UnLoad(){
	ClearBuffers();
	//textures
	delete textureBlank;
	delete textureGame;
	delete textureRGB;
	delete textureShadowDepth;

	for(map<string,Texture*>::iterator key=skinTextures.begin();key!=skinTextures.end();key++){
		delete (*key).second;
	}
	skinTextures.clear();

	texturePos8.clear();
	texturePos16.clear();
	texturePos8x4.clear();
	texturePos16x8.clear();

	gameCursor.clear();

	//models
	delete coordsModel;

	for(int i=0;i<NUM_WEAPONS;i++){
		delete weaponModels[i]->texture;
		delete weaponModels[i];
	}
	weaponModels.clear();

	//shaders
	UnLoadShader(shader3d);
	UnLoadShader(shader2d);
}
void Resources::ClearBuffers(){
	StringTexture::ClearBuffers();
	for(map<int,TTF_Font*>::iterator key=fonts.begin();key!=fonts.end();key++){
		TTF_CloseFont((*key).second);
	}
	fonts.clear();
}
TTF_Font* Resources::LoadFont(int size){
	map<int,TTF_Font*>::iterator key=fonts.find(size);
	if(key!=fonts.end()){
		return key->second;
	}
	else{
		TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size*2);
		if(!font){
			Console::Err("Error Loading Font: " + fontPath + "(" + to_string(size) + ") : " + string(TTF_GetError()));
			return font;
		}
		fonts.insert(fonts.begin(),pair<int,TTF_Font*>(size,font));
		Console::Info("Font loaded " + fontPath);
		return font;
	}
}
char* filetobuf(string file)
{
	FILE *fptr;
	long length;
	char *buf;
	fptr = fopen(file.c_str(), "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length+1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}
void Resources::UnLoadShader(GLuint &shader)
{
	glDeleteProgram(shader);
	shader = 0;
}
bool Resources::LoadShader(string filepath, GLuint &shader)
{
	string firstpath = g_System()->GetDataFile(filepath);

	GLchar *vertexsource, *fragmentsource,*geometrysource;
	GLuint vertexshader, fragmentshader,geometryshader;
	int IsCompiled_VS, IsCompiled_FS,IsCompiled_GS;
	int IsLinked;
	int maxLength;
	char *vertexInfoLog;
	char *fragmentInfoLog;
	char *geometryInfoLog;
	char *shaderProgramInfoLog;
	string path=firstpath;
	path.append(".vert");
	vertexsource = filetobuf(path);
	path=firstpath;
	path.append(".frag");
	fragmentsource = filetobuf(path);
	path=firstpath;
	path.append(".geom");
	geometrysource = filetobuf(path);

	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if(IsCompiled_VS == GL_FALSE)
	{
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);

		vertexInfoLog = (char *)malloc(maxLength);

		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		Console::Err(string(vertexInfoLog));
		free(vertexInfoLog);
	}

	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
	if(IsCompiled_FS == GL_FALSE)
	{
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);

		fragmentInfoLog = (char *)malloc(maxLength);

		glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
		Console::Err(string(fragmentInfoLog));
		free(fragmentInfoLog);
	}
	if(geometrysource!=NULL){
		geometryshader = glCreateShader(GL_GEOMETRY_SHADER);

		glShaderSource(geometryshader, 1, (const GLchar**)&geometrysource, 0);

		glCompileShader(geometryshader);

		glGetShaderiv(geometryshader, GL_COMPILE_STATUS, &IsCompiled_GS);
		if(IsCompiled_GS == GL_FALSE)
		{
			glGetShaderiv(geometryshader, GL_INFO_LOG_LENGTH, &maxLength);

			geometryInfoLog = (char *)malloc(maxLength);

			glGetShaderInfoLog(geometryshader, maxLength, &maxLength, geometryInfoLog);
			Console::Err(string(geometryInfoLog));
			free(geometryInfoLog);
		}
	}

	shader = glCreateProgram();

	glAttachShader(shader, vertexshader);
	glAttachShader(shader, fragmentshader);
	if(geometrysource!=NULL)
		glAttachShader(shader, geometryshader);

	glLinkProgram(shader);


	glGetProgramiv(shader, GL_LINK_STATUS, (int *)&IsLinked);
	if(IsLinked == GL_FALSE)
	{
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		shaderProgramInfoLog = (char *)malloc(maxLength);

		glGetProgramInfoLog(shader, maxLength, &maxLength, shaderProgramInfoLog);

		Console::Err(string(shaderProgramInfoLog));
		free(shaderProgramInfoLog);
	}
	free(vertexsource);
	free(fragmentsource);
	if(geometrysource!=NULL)
		free(geometrysource);
	return true;
}
