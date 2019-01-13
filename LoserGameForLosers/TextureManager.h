#pragma once

#include "SDL.h"
#include "SDL_Image.h"
#include <string>
#include "Game.h"
#include "Atlas.h"

class TextureManager
{
public:
	static SDL_Texture* load_texture(const char* filename);
	static void draw(SDL_Texture * tex, SpriteAddress * address, SDL_Rect * dest, int rots, SDL_RendererFlip flip);
private:
};