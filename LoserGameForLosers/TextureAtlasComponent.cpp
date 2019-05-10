#include "stdafx.h"

TextureAtlasComponent::TextureAtlasComponent()
	: slot_count_(0)
{
	data_ = Game::data->get_atlas_data();
}

TextureAtlasComponent::~TextureAtlasComponent()
{
	slots_.clear();
	data_ = nullptr;
}

int TextureAtlasComponent::create_image_slot(const int sprite_id, const int x, const int y, const int rotation, const SDL_RendererFlip flip, const int slot_id)
{
	if (slot_id < 0)
	{
		slots_.push_back(new ImageSlot(data_, sprite_id, x, y, rotation, flip));
		return slot_count_++;
	}
	slots_[slot_id] = new ImageSlot(data_, sprite_id, x, y, rotation, flip);
	return slot_id;
}

int TextureAtlasComponent::create_animated_slot(const int x, const int y, const int speed, const int frames, const int sprite_id, const int rotation, const SDL_RendererFlip flip, const int slot_id)
{
	auto anim_slot = new AnimatedSlot(data_, x, y);
	anim_slot->add_animated_state(speed, frames, sprite_id, rotation, flip);
	if (slot_id < 0)
	{
		slots_.push_back(anim_slot);
		return slot_count_++;
	}

	slots_[slot_id] = anim_slot;
	return slot_id;
}

int TextureAtlasComponent::create_null_slot(const int slot_id)
{
	if (slot_id < 0)
	{
		slots_.push_back(new Slot(nullptr));
		return slot_count_++;
	}

	slots_[slot_id] = new Slot(nullptr);
	return slot_id;
}

void TextureAtlasComponent::update_image_slot(const int slot_id, const int updated_tex, const int rotation, const SDL_RendererFlip flip)
{
	slots_[slot_id]->set_call(updated_tex, rotation, flip);
}

void TextureAtlasComponent::update_position_and_scaling(const int slot_id, const Vector2D position, const float scale)
{
	slots_[slot_id]->update_position_and_scaling(position, scale);
}

void TextureAtlasComponent::update_position(const int slot_id, const Vector2D position)
{
	slots_[slot_id]->update_position(position);

}

void TextureAtlasComponent::update_scaling(const int slot_id, const float scale)
{
	slots_[slot_id]->update_scaling(scale);
}

void TextureAtlasComponent::update_dimensions(const int slot_id, const int width, const int height)
{
	slots_[slot_id]->update_dimensions(width, height);
}

void TextureAtlasComponent::update_height(const int slot_id, const int height)
{
	slots_[slot_id]->update_height(height);
}

void TextureAtlasComponent::update_width(const int slot_id, const int width)
{
	slots_[slot_id]->update_width(width);
}

void TextureAtlasComponent::add_animation_state(const int slot_id, const int speed, const int frames, const int sprite_id, const int rotation, const SDL_RendererFlip flip)
{
	auto anim_slot = dynamic_cast<Animated*>(slots_[slot_id]);

	if (anim_slot)
		anim_slot->add_animated_state(speed, frames, sprite_id, rotation, flip);
}

void TextureAtlasComponent::update_animation(const int slot_id, const int state)
{
	auto anim_slot = dynamic_cast<Animated*>(slots_[slot_id]);

	if (anim_slot)
		anim_slot->update_animation(state);
}

void TextureAtlasComponent::set_animated_call(const int slot_id, const int state, const int call_id)
{
	auto anim_slot = dynamic_cast<Animated*>(slots_[slot_id]);

	if (anim_slot)
		anim_slot->set_animated_call(state, call_id);
}

void TextureAtlasComponent::draw()
{
	for (auto i = 0; i < slot_count_; i++)
		slots_[i]->draw();
}
