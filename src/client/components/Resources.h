#ifndef RESOURCES_H
#define RESOURCES_H

#include "../ClientComponent.h"

#include <vector>
#include <string>
#include <map>
#include <tools/Protocol.h>
#include <tools/vmath.h>
#include <client/components/graphics/Texture.h>
#include <client/components/graphics/models/Model3d.h>

class Texture;

class Resources : public ClientComponent {
private:
	Resources();
	friend Resources *g_Resources();

public:
	~Resources() override;

	// textures
public:
	std::vector<quad2> texturePos8;
	std::vector<quad2> texturePos8x4;
	std::vector<quad2> texturePos16;
	std::vector<quad2> texturePos16x8;
	std::map<std::string, Texture> skinTextures;
	Texture textureBlank;
	Texture textureRGB;
	Texture textureGame;
	Texture textureCursor;
	std::vector<quad2> gameCursor;

	// models
public:
	std::vector<Model3d> weaponModels;
	std::vector<Model3d> eyesModels;
	Model3d coordsModel;
	Model3d hookHead;
	Model3d hookBody;

private:
	static const char *weaponFiles[NUM_WEAPONS];
};
Resources *g_Resources();

#endif
