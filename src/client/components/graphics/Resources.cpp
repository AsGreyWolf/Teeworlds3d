#include "Resources.h"
#include "../../Client.h"
#include "Model.h"
#include "../Graphics.h"
#include "../../../tools/system.h"
#include "../../../../other/sdl/include/SDL_image.h"

const char* Resources::weaponFiles[NUM_WEAPONS]={
	"models/hummer.model",
	"models/gun.model",
	"models/shotgun.model",
	"models/grenade.model",
	"models/rifle.model",
	"models/ninja.model",
};
const char* Resources::weaponTextureFiles[NUM_WEAPONS]={
	"models/hummer.png",
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
	loadTexture("blank.png",textureBlank,true,false);
	loadTexture("rgb.png",textureRGB,true,false);
	loadTexture("game.png",textureGame,true,true);
	vector<string> skins;
	System::GetFilesInDirectory(skins,m_Graphics->m_Client->GetDataFile("skins"));
	for(unsigned int i=0;i<skins.size();i++){
		GLuint skintex=textureBlank;
		loadTexture("skins/"+skins[i],skintex,true,true);
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
	coordsModel=new Model(GL_LINES,m_Graphics,false);
	coordsModel->texture=textureRGB;
	coordsModel->addVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->addVertex(vec3(32,0,0),vec3(0,0,1),vec2(0,0));
	coordsModel->addVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->addVertex(vec3(0,32,0),vec3(0,0,1),vec2(1,0));
	coordsModel->addVertex(vec3(0,0,0),vec3(0,0,1),vec2(0.5f,0.5f));
	coordsModel->addVertex(vec3(0,0,32),vec3(0,0,1),vec2(0,1));
	coordsModel->create();

	for(int i=0;i<NUM_WEAPONS;i++){
		Model* buffer;
		buffer=new Model(m_Graphics);
		buffer->addObjModel(weaponFiles[i]);
		buffer->create();
		loadTexture(weaponTextureFiles[i],buffer->texture,true,false);
		weaponModels.push_back(buffer);
	}

	//shaders
	loadShader("shaders/shader",shader3d);
	loadShader("shaders/shader2d",shader2d);

	//fonts
	fontPath=m_Graphics->m_Client->GetDataFile(fontName);
}
void Resources::UnLoad(){
	ClearBuffers();
	//textures
	unLoadTexture(textureBlank);
	unLoadTexture(textureGame);
	unLoadTexture(textureRGB);

	for(map<string,GLuint>::iterator key=skinTextures.begin();key!=skinTextures.end();key++){
		unLoadTexture((*key).second);
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
		unLoadTexture(weaponModels[i]->texture);
		delete weaponModels[i];
	}
	weaponModels.clear();

	//shaders
	unLoadShader(shader3d);
	unLoadShader(shader2d);
}
void Resources::ClearBuffers(){
	for(map<int,map<string,GLuint>>::iterator key=stringBuffer.begin();key!=stringBuffer.end();key++){
		for(map<string,GLuint>::iterator datakey=(*key).second.begin();datakey!=(*key).second.end();datakey++){
			unLoadTexture((*datakey).second);
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
bool Resources::loadStringTexture(GLuint& tex,float &aspect,string data,int size,bool buffering){
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
			TTF_Font* font=loadFont(size);
			if(font!=NULL){
				SDL_Surface* surface = TTF_RenderUTF8_Blended(font, data.c_str(), m_Graphics->m_Resources->SDLColorWhite);
				if(surface!=NULL){
					m_Graphics->m_Resources->loadTextureFromSurface(surface,texture,true,false);
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
		TTF_Font* font=loadFont(size);
		if(font!=NULL){
			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, data.c_str(), m_Graphics->m_Resources->SDLColorWhite);
			if(surface!=NULL){
				m_Graphics->m_Resources->loadTextureFromSurface(surface,tex,false,true);
				aspect=surface->w*1.0f/surface->h;
				SDL_FreeSurface(surface);
				complete=true;
			}
		}
	}
	return complete;
}
TTF_Font* Resources::loadFont(int size){
	map<int,TTF_Font*>::iterator key=fonts.find(size);
	if(key!=fonts.end()){
		return key->second;
	}
	else{
		TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size*2);
		if(font==NULL){
			m_Graphics->m_Client->Err("Error Loading Font: "+fontPath+"("+to_string(size)+") : "+string(TTF_GetError()));
			return font;
		}
		fonts.insert(fonts.begin(),pair<int,TTF_Font*>(size,font));
		m_Graphics->m_Client->Info("Font loaded "+fontPath);
		return font;
	}
}
void Resources::unLoadTexture(GLuint &tex){
	glDeleteTextures(1,&tex);
}
bool Resources::loadTextureFromSurface(SDL_Surface* &data, GLuint &tex,bool mipmaps,bool filtering)
{
	m_Graphics->to_RGBA(data);
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

	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
	if(!filtering){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}else{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	if(mipmaps)
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, data->w, data->h,GL_RGBA, GL_UNSIGNED_BYTE,  data->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->w, data->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->pixels);
	return true;
}

bool Resources::loadTexture(string filepath, GLuint &tex,bool mipmaps,bool filtering)
{
	string path=m_Graphics->m_Client->GetDataFile(filepath);
	SDL_Surface *temp = NULL;
	temp = IMG_Load(path.c_str());
	if(!loadTextureFromSurface(temp,tex,mipmaps,filtering)){
		m_Graphics->m_Client->Err("Error Loading Texture: "+filepath+" : "+string(SDL_GetError()));
		SDL_FreeSurface(temp);
		return false;
	}
	SDL_FreeSurface(temp);
	m_Graphics->m_Client->Info("Texture loaded "+filepath);
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
void Resources::unLoadShader(GLuint &shader)
{
	// TODO unload shaders
}
bool Resources::loadShader(string filepath, GLuint &shader)
{
	string firstpath=m_Graphics->m_Client->GetDataFile(filepath);

	GLchar *vertexsource, *fragmentsource;
	GLuint vertexshader, fragmentshader;
	int IsCompiled_VS, IsCompiled_FS;
	int IsLinked;
	int maxLength;
	char *vertexInfoLog;
	char *fragmentInfoLog;
	char *shaderProgramInfoLog;
	string path=firstpath;
	path.append(".vert");
	vertexsource = filetobuf(path);
	path=firstpath;
	path.append(".frag");
	fragmentsource = filetobuf(path);

	vertexshader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);

	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if(IsCompiled_VS == GL_FALSE)
	{
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);

		vertexInfoLog = (char *)malloc(maxLength);

		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		m_Graphics->m_Client->Err(string(vertexInfoLog));
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
		m_Graphics->m_Client->Err(string(fragmentInfoLog));
		free(fragmentInfoLog);
	}

	shader = glCreateProgram();

	glAttachShader(shader, vertexshader);
	glAttachShader(shader, fragmentshader);

	glLinkProgram(shader);


	glGetProgramiv(shader, GL_LINK_STATUS, (int *)&IsLinked);
	if(IsLinked == GL_FALSE)
	{
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		shaderProgramInfoLog = (char *)malloc(maxLength);

		glGetProgramInfoLog(shader, maxLength, &maxLength, shaderProgramInfoLog);

		m_Graphics->m_Client->Err(string(shaderProgramInfoLog));
		free(shaderProgramInfoLog);
	}
	free(vertexsource);
	free(fragmentsource);
	return true;
}
