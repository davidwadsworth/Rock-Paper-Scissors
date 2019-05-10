#pragma once
#include "ECS.h"
#include "TextureSlot.h"

/**
 * TextureAtlasComponent 
 * -------------------------
 * Creates and Updates images from dynamically sized vector of "Slots" created from data 
 */

class TextureAtlasComponent : public Component
{
	std::vector<Slot*> slots_;
	int slot_count_;
	AtlasData* data_;
public:

	TextureAtlasComponent();
	~TextureAtlasComponent();

	int create_null_slot( int slot_id = -1);

	// Standard image to store in slot 
	int create_image_slot(int sprite_id, int x, int y, int rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, int slot_id = -1);
	void update_image_slot(int slot_id, int updated_tex, int rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void update_position_and_scaling(int slot_id, Vector2D position, float scale);
	void update_position(int slot_id, Vector2D position);
	void update_scaling(int slot_id, float scale);
	void update_dimensions(int slot_id, int width, int height);
	void update_height(int slot_id, int height);
	void update_width(int slot_id, int width);

	// Animated image to store in slot
	int create_animated_slot(int x, int y, int speed, int frames, int sprite_id, int rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, int slot_id = -1);
	void add_animation_state(int slot_id, int speed, int frames, int sprite_id, int rotation = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void update_animation(int slot_id, int state);
	void set_animated_call(int slot_id, int state, int call_id);

	void draw() override;
};
