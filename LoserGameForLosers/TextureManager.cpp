#include "stdafx.h"
#include "TextureManager.h"
#include "Constants.h"

SDL_Texture* TextureManager::load_texture(const char* texture)
{
	const auto temp_surface = IMG_Load(texture);
	const auto tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	return tex;
}


void TextureManager::draw(SDL_Texture * tex, SpriteAddress * address, SDL_Rect * dest, int rots, SDL_RendererFlip flip)
{
	auto src = new SDL_Rect{ address->x, address->y, address->width, address->height };

	dest->x -= address->x_offset;
	dest->y -= address->y_offset;
	rots += address->rotation;

	SDL_RenderCopyEx(Game::renderer, tex, src, dest, rots, nullptr, flip);
	
}
