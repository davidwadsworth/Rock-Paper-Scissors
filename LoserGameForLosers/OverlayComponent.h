#pragma once
#include "ECS.h"

class OverlayComponent : public Component
{
	int container_id_, bar_id_, container_slot_{}, bar_slot_{}, remaining_health_, original_bar_width_, bar_width_, bar_height_;
	TextureAtlasComponent * texture_;
	SDL_RendererFlip flip_;
	Vector2D bar_position_;
public:
	OverlayComponent(int container_id, int bar_id, SDL_RendererFlip flip);

	void init() override;
	void update() override;

	void deal_damage(int damage);
	bool is_depleted() const;
};