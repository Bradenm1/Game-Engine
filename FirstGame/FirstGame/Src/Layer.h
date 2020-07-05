#pragma once

class SpriteSheet;
class Layer {
public:
	SpriteSheet* Spritesheet;
	bool Cancolide;

	Layer(SpriteSheet* SpriteSheet, bool CanColide);
};