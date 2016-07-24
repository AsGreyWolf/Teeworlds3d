#include "ImageLoader.h"
#include <shared/Console.h>
#include <shared/System.h>
#include <SDL_image.h>
#ifdef __ANDROID__
#include <tools/android.h>
#endif

class ImageLoader *pImageLoader;
ImageLoader *g_ImageLoader() {
	return pImageLoader ? pImageLoader : new ImageLoader();
}

ImageLoader::ImageLoader() : ClientComponent() {
	pImageLoader = this;
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		g_Console()->Err("Unable to initialize SDL_IMG: " +
		                 std::string(IMG_GetError()));
		return; // TODO: need exceptions
	}
	SDL_version ver = *IMG_Linked_Version();
	g_Console()->Info("Initialized SDL_IMG " + std::to_string(ver.major) + "." +
	                  std::to_string(ver.minor) + "." + std::to_string(ver.patch));
}
ImageLoader::~ImageLoader() {
	IMG_Quit();
	pImageLoader = 0;
}
Texture ImageLoader::Load(std::string path, int flags) {
	Texture t;
	SDL_Surface *temp;
	if ((temp = IMG_Load(g_System()->GetDataFile(path).c_str())) == NULL) {
		g_Console()->Err("Error Loading Texture: " + path + " : " +
		                 std::string(IMG_GetError()));
		return t;
	}
	t = Texture(temp, flags);
	SDL_FreeSurface(temp);

	g_Console()->Info("Texture loaded " + path);
	return t;
}
