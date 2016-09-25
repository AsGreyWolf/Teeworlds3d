#include "Resources.h"

#include <client/components/ImageLoader.h>
#include <client/components/Loading.h>
#include <client/components/graphics/geometry/ObjModel.h>
#include <client/components/graphics/geometry/Primitives.h>
#include <client/components/graphics/models/PlayerModel.h> //TODO: REMOVE !!!!
#include <shared/System.h>

const char *Resources::weaponFiles[NUM_WEAPONS] = {
    "models/hammer",  "models/gun",   "models/shotgun",
    "models/grenade", "models/rifle", "models/ninja",
};

class Resources *pResources;
Resources *g_Resources() { return pResources ? pResources : new Resources(); }

Resources::Resources() : ClientComponent() {
	pResources = this;
	// textures
	textureRGB = g_ImageLoader()->Load(std::string("rgb.png"), TEXTURE_ANISOTROPY);
	textureBlank =
	    g_ImageLoader()->Load(std::string("blank.png"), TEXTURE_ANISOTROPY);
	textureGame = g_ImageLoader()->Load(std::string("game.png"),
	                                    TEXTURE_ANISOTROPY | TEXTURE_FILTERING);
	textureCursor = g_ImageLoader()->Load(std::string("gui_cursor.png"),
	                                      TEXTURE_ANISOTROPY | TEXTURE_FILTERING);
	std::vector<std::string> skins =
	    g_System()->GetFilesInDirectory(g_System()->GetDataFile("skins"));
	for (const std::string &skin : skins) {
		skinTextures[skin.substr(0, skin.size() - 4)] = textureRGB;
		g_Loading()->Push([&, skin]() {
			Texture skintex = g_ImageLoader()->Load("skins/" + skin);
			skinTextures[skin.substr(0, skin.size() - 4)] = skintex;
		});
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

	weaponModels.resize(NUM_WEAPONS);
	for (int i = 0; i < NUM_WEAPONS; i++) {
		g_Loading()->Push([&, i]() {
			Model3d buffer;
			buffer.Add(ObjModel(weaponFiles[i]));
			buffer.texture = g_ImageLoader()->Load(std::string(weaponFiles[i]) + ".png",
			                                       TEXTURE_ANISOTROPY);
			weaponModels[i] = buffer;
		});
	}
	eyesModels.resize(NUM_EMOTES);
	for (int i = 0; i < NUM_EMOTES; i++) {
		g_Loading()->Push([&, i]() {
			Model3d buffer(false);
			buffer.Add(
			    Quad(quad3(glm::vec3(-PlayerModel::eyeScale - PlayerModel::eyeSeparation,
			                         0, PlayerModel::eyeScale),
			               glm::vec3(0 - PlayerModel::eyeSeparation, 0,
			                         PlayerModel::eyeScale),
			               glm::vec3(0 - PlayerModel::eyeSeparation, 0, 0),
			               glm::vec3(-PlayerModel::eyeScale - PlayerModel::eyeSeparation,
			                         0, 0)),
			         glm::vec3(0, 1, 0), texturePos8x4[26 + i].reflectX()));
			buffer.Add(Quad(
			    quad3(
			        glm::vec3(0 + PlayerModel::eyeSeparation, 0, PlayerModel::eyeScale),
			        glm::vec3(PlayerModel::eyeScale + PlayerModel::eyeSeparation, 0,
			                  PlayerModel::eyeScale),
			        glm::vec3(PlayerModel::eyeScale + PlayerModel::eyeSeparation, 0, 0),
			        glm::vec3(PlayerModel::eyeSeparation, 0, 0)),
			    glm::vec3(0, 1, 0), texturePos8x4[26 + i]));
			buffer.texture = skinTextures["default"];
			eyesModels[i] = buffer;
		});
	}
	g_Loading()->Push([&]() { hookHead.Add(ObjModel("models/hook0")); });
	g_Loading()->Push([&]() { hookBody.Add(ObjModel("models/hook")); });
	g_Loading()->Push([&]() {
		hookBody.texture = hookHead.texture =
		    g_ImageLoader()->Load("models/hook.png");
	});
}
Resources::~Resources() {
	skinTextures.clear();

	texturePos8.clear();
	texturePos16.clear();
	texturePos8x4.clear();
	texturePos16x8.clear();

	gameCursor.clear();

	weaponModels.clear();
	pResources = nullptr;
}
