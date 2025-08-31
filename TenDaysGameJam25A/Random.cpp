#include "Random.h"

float Random::RandomFloat(float min, float max) { return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min); }

int Random::RandomInt(int min, int max) {
	// スワップ
	if (max < min) {
		int tmp = min;
		min = max;
		max = tmp;
	}

	// ゼロ除算対策
	if (max == min) {
		return min;
	}

	return min + rand() % (max - min + 1);
}
