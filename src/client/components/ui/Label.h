#ifndef LABEL_H
#define LABEL_H

#include "Image.h"
#include <client/components/TextGenerator.h>

class Label : public Image {
public:
	Label(const std::string &str, int size = FONT_NORMAL);
	Label(const Label &second);

	void SetText(const std::string &str, int size = FONT_NORMAL);
};

#endif
