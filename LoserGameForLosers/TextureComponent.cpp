#include "stdafx.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(const int texture_id)
	: texture_id_(texture_id)
{}

void TextureComponent::set_blend_mode(const SDL_BlendMode blending) const
{
	SDL_SetTextureBlendMode(call_.tex, blending);
}

void TextureComponent::set_color(const Uint8 red, const Uint8 green, const Uint8 blue) const
{
	SDL_SetTextureColorMod(call_.tex, red, green, blue);
}

void TextureComponent::set_alpha(const Uint8 alpha) const
{
	SDL_SetTextureAlphaMod(call_.tex, alpha);
}

void TextureComponent::init()
{
	const auto transform = entity->get_component<TransformComponent>();

	dest_ = { static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), static_cast<int>(transform.width * transform.scale_2d.x), static_cast<int>(transform.height * transform.scale_2d.y) };
	src_ = { 0, 0, transform.width, transform.height };

	call_ = DrawCall(texture_id_, &src_, &dest_, SDL_FLIP_NONE, 0, nullptr);
}

void TextureComponent::draw()
{
	TextureManager::draw(&call_);
}
