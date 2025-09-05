#include "Click.h"
void Click::Update() {
	memcpy(preClicks_, clicks_, 8);
	for (int i = 0; i < 8; i++) {
		clicks_[i] = Novice::IsPressMouse(i);
	}
}