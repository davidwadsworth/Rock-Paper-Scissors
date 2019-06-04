#pragma once
#include "ECS.h"
#include "DrawCall.h"

class TextureComponent : public Component
{
	int texture_id_;
	DrawCall call_;
	SDL_Rect dest_, src_;
	SDL_Texture * texture_;
public:
	TextureComponent(int texture_id);
	~TextureComponent() = default;

	void set_blend_mode(SDL_BlendMode blending) const;
	void set_color(Uint8 red, Uint8 green, Uint8 blue) const;
	void set_alpha(Uint8 alpha) const;

	void init() override;
	void draw() override;
};