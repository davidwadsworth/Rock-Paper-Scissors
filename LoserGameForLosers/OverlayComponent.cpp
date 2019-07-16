#include "stdafx.h"
#include "OverlayComponent.h"

OverlayComponent::OverlayComponent(const int container_id, const int bar_id, const SDL_RendererFlip flip)
	: container_id_(container_id), bar_id_(bar_id), remaining_health_(HEALTH_TOTAL), original_bar_width_(0), bar_width_(0), bar_height_(0), texture_(nullptr),
	flip_(flip)
{}

void OverlayComponent::init()
{
	texture_ = &entity->get_component<TextureAtlasComponent>();

	original_bar_width_ = bar_width_ = BAR_WIDTH;
	bar_height_ = BAR_HEIGHT;

	if (flip_)
	{
		bar_position_ = BAR_POSITION_RIGHT;
		container_slot_ = texture_->create_image_slot(container_id_, BAR_RIGHT_CONTAINER_X, BAR_RIGHT_CONTAINER_Y, 0, flip_);
	}
	else
	{
		bar_position_ = BAR_POSITION_LEFT;
		container_slot_ = texture_->create_image_slot(container_id_, BAR_LEFT_CONTAINER_X, BAR_LEFT_CONTAINER_Y, 0, flip_);
	}

	bar_slot_ = texture_->create_image_slot(bar_id_, static_cast<int>(bar_position_.x), static_cast<int>(bar_position_.y), 0, SDL_FLIP_NONE);
}

void OverlayComponent::update()
{
	texture_->update_dimensions(bar_slot_, bar_width_, bar_height_);
	texture_->update_position(bar_slot_, bar_position_);
}

void OverlayComponent::deal_damage(const int damage)
{
	remaining_health_ = (remaining_health_ - damage) > 0 ? remaining_health_ - damage : 0;
	bar_width_ = static_cast<int>(original_bar_width_ * static_cast<double>(remaining_health_) / HEALTH_TOTAL);

	if (!flip_)
		bar_position_.x = static_cast<double>(BAR_POSITION_LEFT.x + original_bar_width_ - bar_width_);
}

bool OverlayComponent::is_depleted() const
{
	return !remaining_health_;
}
