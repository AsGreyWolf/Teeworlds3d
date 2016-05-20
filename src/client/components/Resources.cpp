#include "Resources.h"

#include <shared/System.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/geometry/Primitives.h>
#include <client/components/graphics/geometry/ObjModel.h>
#include <client/components/graphics/models/PlayerModel.h> //TODO: REMOVE !!!!

const char *Resources::weaponFiles[NUM_WEAPONS] = {
    "models/hammer",  "models/gun",   "models/shotgun",
    "models/grenade", "models/rifle", "models/ninja",
};

class Resources *pResources;
Resources *g_Resources() { return pResources ? pResources : new Resources(); }

Resources::Resources() : ClientComponent() {
	pResources = this;
	// textures
	textureRGB = Texture(std::string("rgb.png"), TEXTURE_ANISOTROPY);
	textureBlank = Texture(std::string("blank.png"), TEXTURE_ANISOTROPY);
	textureGame =
	    Texture(std::string("game.png"), TEXTURE_ANISOTROPY | TEXTURE_FILTERING);
	std::vector<std::string> skins;
	g_System()->GetFilesInDirectory(skins, g_System()->GetDataFile("skins"));
	for (unsigned int i = 0; i < skins.size(); i++) {
		Texture skintex("skins/" + skins[i]);
		skins[i].resize(skins[i].size() - 4);
		skinTextures.insert(skinTextures.begin(),
		                    std::pair<std::string, Texture>(skins[i], skintex));
	}
	texturePos8.reserve(8 * 8);
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
			texturePos8.push_back(quad2(1.0f * i / 8, 1.0f * j / 8, 1.0f / 8, 1.0f / 8));
	texturePos16.reserve(16 * 16);
	for (int j = 0; j < 16; j++)
		for (int i = 0; i < 16; i++)
			texturePos16.push_back(
			    quad2(1.0f * i / 16, 1.0f * j / 16, 1.0f / 16, 1.0f / 16));
	texturePos8x4.reserve(8 * 4);
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 8; i++)
			texturePos8x4.push_back(
			    quad2(1.0f * i / 8, 1.0f * j / 4, 1.0f / 8, 1.0f / 4));
	texturePos16x8.reserve(16 * 8);
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 16; i++)
			texturePos16x8.push_back(
			    quad2(1.0f * i / 16, 1.0f * j / 8, 1.0f / 16, 1.0f / 8));

	gameCursor.reserve(NUM_WEAPONS);
	gameCursor.push_back(texturePos16x8[0]);
	gameCursor.push_back(texturePos16x8[32]);
	gameCursor.push_back(texturePos16x8[48]);
	gameCursor.push_back(texturePos16x8[64]);
	gameCursor.push_back(texturePos16x8[96]);
	gameCursor.push_back(texturePos16x8[80]);

	// models
	coordsModel = Model3d(false, GL_LINES);
	coordsModel.texture = textureRGB;
	coordsModel.Add(Line(glm::vec3(0, 0, 0), glm::vec3(32, 0, 0),
	                     glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
	                     glm::vec2(0.5f, 0.5f), glm::vec2(0, 0)));
	coordsModel.Add(Line(glm::vec3(0, 0, 0), glm::vec3(0, 32, 0),
	                     glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
	                     glm::vec2(0.5f, 0.5f), glm::vec2(1, 0)));
	coordsModel.Add(Line(glm::vec3(0, 0, 0), glm::vec3(0, 0, 32),
	                     glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
	                     glm::vec2(0.5f, 0.5f), glm::vec2(0, 1)));

	weaponModels.reserve(NUM_WEAPONS);
	for (int i = 0; i < NUM_WEAPONS; i++) {
		Model3d buffer;
		buffer.Add(ObjModel(weaponFiles[i]));
		buffer.texture =
		    Texture(std::string(weaponFiles[i]) + ".png", TEXTURE_ANISOTROPY);
		weaponModels.push_back(buffer);
	}
	eyesModels.reserve(NUM_EMOTES);
	for (int i = 0; i < NUM_EMOTES; i++) {
		Model3d buffer(false);
		buffer.Add(Quad(
		    quad3(glm::vec3(-PlayerModel::eyescale - PlayerModel::separation, 0,
		                    PlayerModel::eyescale),
		          glm::vec3(0 - PlayerModel::separation, 0, PlayerModel::eyescale),
		          glm::vec3(0 - PlayerModel::separation, 0, 0),
		          glm::vec3(-PlayerModel::eyescale - PlayerModel::separation, 0, 0)),
		    glm::vec3(0, 1, 0), texturePos8x4[26 + i].reflectX()));
		buffer.Add(Quad(
		    quad3(glm::vec3(0 + PlayerModel::separation, 0, PlayerModel::eyescale),
		          glm::vec3(PlayerModel::eyescale + PlayerModel::separation, 0,
		                    PlayerModel::eyescale),
		          glm::vec3(PlayerModel::eyescale + PlayerModel::separation, 0, 0),
		          glm::vec3(PlayerModel::separation, 0, 0)),
		    glm::vec3(0, 1, 0), texturePos8x4[26 + i]));
		buffer.texture = skinTextures["default"];
		eyesModels.push_back(buffer);
	}
	hookHead.Add(ObjModel("models/hook0"));
	hookBody.Add(ObjModel("models/hook"));
	hookBody.texture = hookHead.texture = Texture("models/hook.png");
}
Resources::~Resources() {
	skinTextures.clear();

	texturePos8.clear();
	texturePos16.clear();
	texturePos8x4.clear();
	texturePos16x8.clear();

	gameCursor.clear();

	weaponModels.clear();
	pResources = 0;
}
