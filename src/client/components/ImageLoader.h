#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "../ClientComponent.h"
#include <client/components/graphics/Texture.h>

class ImageLoader : public ClientComponent {
private:
	ImageLoader();
	friend ImageLoader *g_ImageLoader();

public:
	~ImageLoader() override;

	Texture Load(std::string path, int flags = 0);
};
ImageLoader *g_ImageLoader();

#endif
