#include "stdafx.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(const int texture_id)
	: texture_id_(texture_id), dest_(), src_(), texture_(nullptr)
{}

void TextureComponent::set_blend_mode(const SDL_BlendMode blending) const
{
	texture_->set_blend_mode(blending);
}

void TextureComponent::set_color(const Uint8 red, const Uint8 green, const Uint8 blue) const
{
	texture_->set_color(red, green, blue);
}

void TextureComponent::set_alpha(const Uint8 alpha) const
{
	texture_->set_alpha(alpha);
}

void TextureComponent::init()
{
	const auto transform = entity->get_component<TransformComponent>();

	texture_ = GameState::get_palette()->get_texture(texture_id_);

	dest_ = { static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), static_cast<int>(transform.width * transform.scale), static_cast<int>(transform.height * transform.scale) };
	src_ = { 0, 0, transform.width, transform.height };

	call_ = DrawCall( &src_, &dest_, SDL_FLIP_NONE, 0, nullptr);
}

void TextureComponent::draw()
{
	texture_->render(call_.src, call_.dest, call_.rotation, call_.rotation_point, call_.flip);
}
