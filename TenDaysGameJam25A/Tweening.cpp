#include "Tweening.h"

float Tweening::Easing(float t, Ease ease) {
	if (t >= 1.0f) {
		t = 1.0f;
	}

	if (ease == LINEAR) {
		return t;
	} else if (ease == EASE_IN_QUAD) {
		return t * t;
	} else if (ease == EASE_OUT_QUAD) {
		return t * (2.0f - t);
	} else if (ease == EASE_INOUT_QUAD) {
		if (t < 0.5f) {
			return 2.0f * t * t;
		} else {
			return 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
		}
	} else {
		return t;
	}
}
