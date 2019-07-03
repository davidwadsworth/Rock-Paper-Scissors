#include "stdafx.h"
#include "OverlayComponent.h"

OverlayComponent::OverlayComponent(const int container_id, const int bar_id, const SDL_RendererFlip flip)
	: container_id_(container_id), bar_id_(bar_id), remaining_health_(100), original_bar_width_(0), bar_width_(0), bar_height_(0), texture_(nullptr),
	flip_(flip)
{}

void OverlayComponent::init()
{
	texture_ = &entity->get_component<TextureAtlasComponent>();

	original_bar_width_ = bar_width_ = 337;
	bar_height_ = 20;

	if (flip_)
	{
		bar_position_ = { 405, 43 };
		container_slot_ = texture_->create_image_slot(container_id_, 400, 0, 0, flip_);
	}
	else
	{
		bar_position_ = { 58, 43 };
		container_slot_ = texture_->create_image_slot(container_id_, 25, 0, 0, flip_);
	}

	bar_slot_ = texture_->create_image_slot(bar_id_, bar_position_.x, bar_position_.y, 0, SDL_FLIP_NONE);
}

void OverlayComponent::update()
{
	texture_->update_dimensions(bar_slot_, bar_width_, bar_height_);
	texture_->update_position(bar_slot_, bar_position_);
}

void OverlayComponent::deal_damage(const int damage)
{
	remaining_health_ = (remaining_health_ - damage) > 0 ? remaining_health_ - damage : 0;
	bar_width_ = original_bar_width_ * static_cast<double>(remaining_health_) / 100.0;

	if (!flip_)
		bar_position_.x = 58 + original_bar_width_ - bar_width_;
}

bool OverlayComponent::is_depleted() const
{
	return !remaining_health_;
}
