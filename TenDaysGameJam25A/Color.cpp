#include "Color.h"

unsigned int Color::RGBCreator(int red, int green, int blue, int alpha) {
	return (red * static_cast<int>(powf(16.0f, 6.0f))) + (green * static_cast<int>(powf(16.0f, 4.0f))) + (blue * static_cast<int>(powf(16.0f, 2.0f))) + alpha;
}

int Color::RGBPickUp(unsigned int color, PickUpColor pickUpColor) {
	unsigned int returnColor = 0x00;
	unsigned int tempColor;

	switch (pickUpColor) {
	case PickUpColor::kPickUpRed:
		returnColor = color / static_cast<int>(powf(16.0f, 6.0f));
		break;
	case PickUpColor::kPickUpGreen:

		tempColor = color / static_cast<int>(powf(16.0f, 6.0f));

		returnColor = tempColor;
		break;
	case PickUpColor::kPickUpBlue:
		tempColor = color / static_cast<int>(powf(16.0f, 4.0f));
		tempColor = tempColor * static_cast<int>(powf(16.0f, 4.0f));

		color -= tempColor;

		returnColor = color / static_cast<int>(powf(16.0f, 2.0f));
		break;
	case PickUpColor::kPickUpAlpha:
		tempColor = color / static_cast<int>(powf(16.0f, 2.0f));
		tempColor = tempColor * static_cast<int>(powf(16.0f, 2.0f));

		color -= tempColor;

		returnColor = color;
		break;
	}

	return returnColor;
}
