#include "Resources.h"
#include "../../../shared/Console.h"
#include "../../../shared/System.h"
#include "../../Client.h"
#include "Model.h"
#include "../Graphics.h"
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
	LoadTexture(textureBlank,true,false,"blank.png");
	LoadTexture(textureRGB,true,false,"rgb.png");
	LoadTexture(textureGame,true,true,"game.png");
	GenTexture(textureShadowDepth, g_Graphics()->screenSize*g_Graphics()->aspect * 4, g_Graphics()->screenSize*g_Graphics()->aspect * 4, true, true, true, NULL);
	vector<string> skins;
	g_System()->GetFilesInDirectory(skins, g_System()->GetDataFile("skins"));
	for(unsigned int i=0;i<skins.size();i++){
		GLuint skintex=textureBlank;
		LoadTexture(skintex,true,false,"skins/"+skins[i]);
		skins[i].resize(skins[i].size()-4);
		skinTextures.insert(skinTextures.begin(),pair<string,GLuint>(skins[i],skintex));
	}
	texturePos8.push_back(quad2(0.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,0.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,1.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,2.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,3.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,4.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,5.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,6.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(0.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(1.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(2.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(3.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(4.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(5.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(6.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos8.push_back(quad2(7.0f/8,7.0f/8,1.0f/8,1.0f/8));
	texturePos16.push_back(quad2(0.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,0.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,1.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,2.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,3.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,4.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,5.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,6.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,7.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,8.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,9.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,10.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,11.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,12.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,13.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,14.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(0.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(1.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(2.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(3.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(4.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(5.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(6.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(7.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(8.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(9.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(10.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(11.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(12.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(13.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(14.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos16.push_back(quad2(15.0f/16,15.0f/16,1.0f/16,1.0f/16));
	texturePos8x4.push_back(quad2(0.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(1.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(2.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(3.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(4.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(5.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(6.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(7.0f/8,0.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(0.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(1.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(2.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(3.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(4.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(5.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(6.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(7.0f/8,1.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(0.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(1.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(2.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(3.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(4.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(5.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(6.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(7.0f/8,2.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(0.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(1.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(2.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(3.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(4.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(5.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(6.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos8x4.push_back(quad2(7.0f/8,3.0f/4,1.0f/8,1.0f/4));
	texturePos16x8.push_back(quad2(0.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,0.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,1.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,2.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,3.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,4.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,5.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,6.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(0.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(1.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(2.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(3.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(4.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(5.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(6.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(7.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(8.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(9.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(10.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(11.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(12.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(13.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(14.0f/16,7.0f/8,1.0f/16,1.0f/8));
	texturePos16x8.push_back(quad2(15.0f/16,7.0f/8,1.0f/16,1.0f/8));

	gameCursor.push_back(texturePos16x8[0]);
	gameCursor.push_back(texturePos16x8[32]);
	gameCursor.push_back(texturePos16x8[48]);
	gameCursor.push_back(texturePos16x8[64]);
	gameCursor.push_back(texturePos16x8[96]);
	gameCursor.push_back(texturePos16x8[80]);

	//models
	coordsModel=new Model(GL_LINES,false);
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
		LoadTexture(buffer->texture,true,false,weaponTextureFiles[i]);
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
	UnLoadTexture(textureBlank);
	UnLoadTexture(textureGame);
	UnLoadTexture(textureRGB);
	RemoveTexture(textureShadowColor);
	RemoveTexture(textureShadowDepth);

	for(map<string,GLuint>::iterator key=skinTextures.begin();key!=skinTextures.end();key++){
		UnLoadTexture((*key).second);
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
		UnLoadTexture(weaponModels[i]->texture);
		delete weaponModels[i];
	}
	weaponModels.clear();

	//shaders
	UnLoadShader(shader3d);
	UnLoadShader(shader2d);
}
void Resources::ClearBuffers(){
	for(map<int,map<string,GLuint>>::iterator key=stringBuffer.begin();key!=stringBuffer.end();key++){
		for(map<string,GLuint>::iterator datakey=(*key).second.begin();datakey!=(*key).second.end();datakey++){
			UnLoadTexture((*datakey).second);
		}
		(*key).second.clear();
	}
	stringBuffer.clear();
	for(map<int,map<string,float>>::iterator key=aspectBuffer.begin();key!=aspectBuffer.end();key++){
		(*key).second.clear();
	}
	aspectBuffer.clear();
	for(map<int,TTF_Font*>::iterator key=fonts.begin();key!=fonts.end();key++){
		TTF_CloseFont((*key).second);
	}
	fonts.clear();
}
bool Resources::LoadStringTexture(GLuint& tex,float &aspect,string data,int size,bool buffering){
	tex=textureRGB;
	aspect=1;
	bool complete=false;
	if(buffering){
		map<int,map<string,GLuint>>::iterator key=stringBuffer.find(size);
		if(key==stringBuffer.end()){
			stringBuffer.insert(stringBuffer.begin(),pair<int,map<string,GLuint>>(size,map<string,GLuint>()));
			aspectBuffer.insert(aspectBuffer.begin(),pair<int,map<string,float>>(size,map<string,float>()));
			key=stringBuffer.find(size);
		}
		map<string,GLuint>::iterator datakey=(*key).second.find(data);
		if(datakey==(*key).second.end()){
			GLuint texture=-1;
			float aspect=1;
			TTF_Font* font=LoadFont(size);
			if(font!=NULL){
				SDL_Surface* surface = TTF_RenderUTF8_Blended(font, data.c_str(), SDLColorWhite);
				if(surface!=NULL){
					LoadTextureFromSurface(texture, true, true, surface);
					aspect=surface->w*1.0f/surface->h;
					SDL_FreeSurface(surface);
					complete=true;
				}
				(*key).second.insert((*key).second.begin(),pair<string,GLuint>(data,texture));
				datakey=(*key).second.find(data);
				aspectBuffer.at(size).insert(aspectBuffer.at(size).begin(),pair<string,float>(data,aspect));
			}
		}
		else{
			complete=true;
		}
		if(complete){
			tex=(*datakey).second;
			aspect=aspectBuffer.at(size).at(data);
		}
	}else{
		TTF_Font* font=LoadFont(size);
		if(font!=NULL){
			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, data.c_str(), SDLColorWhite);
			if(surface!=NULL){
				LoadTextureFromSurface(tex, true, true, surface);
				aspect=surface->w*1.0f/surface->h;
				SDL_FreeSurface(surface);
				complete=true;
			}
		}
	}
	return complete;
}
TTF_Font* Resources::LoadFont(int size){
	map<int,TTF_Font*>::iterator key=fonts.find(size);
	if(key!=fonts.end()){
		return key->second;
	}
	else{
		TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size*2);
		if(font==NULL){
			Console::Err("Error Loading Font: " + fontPath + "(" + to_string(size) + ") : " + string(TTF_GetError()));
			return font;
		}
		fonts.insert(fonts.begin(),pair<int,TTF_Font*>(size,font));
		Console::Info("Font loaded " + fontPath);
		return font;
	}
}
void Resources::GenTexture(GLuint &tex, int w, int h, bool isDepth, bool anisotropy, bool filtering, const GLvoid* pixels){
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_2D);
	int anisotropyI;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropyI);
	if (anisotropy)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropyI);//TODO anisotropy filterring
	if(!filtering){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}else{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	if(isDepth) glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);
	else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}
void Resources::RemoveTexture(GLuint &tex){
	glDeleteTextures(1,&tex);
}
void Resources::UnLoadTexture(GLuint &tex){
	RemoveTexture(tex);
}
bool Resources::LoadTextureFromSurface(GLuint &tex, bool anisotropy, bool filtering, SDL_Surface* &data)
{
	g_Graphics()->to_RGBA(data);
	GLint maxTexSize;
	if(data == NULL){
		tex=textureRGB;
		return false;
	}
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if(data->w > maxTexSize){
		tex=textureRGB;
		return false;
	}
	GenTexture(tex, data->w, data->h, false, anisotropy, filtering, data->pixels);
	return true;
}

bool Resources::LoadTexture(GLuint &tex, bool anisotropy, bool filtering, string filepath)
{
	string path = g_System()->GetDataFile(filepath);
	SDL_Surface *temp = NULL;
	temp = IMG_Load(path.c_str());
	if (!LoadTextureFromSurface(tex, anisotropy, filtering, temp)){
		Console::Err("Error Loading Texture: " + filepath + " : " + string(SDL_GetError()));
		SDL_FreeSurface(temp);
		return false;
	}
	SDL_FreeSurface(temp);
	Console::Info("Texture loaded " + filepath);
	return true;
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
	// TODO unload shaders
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
