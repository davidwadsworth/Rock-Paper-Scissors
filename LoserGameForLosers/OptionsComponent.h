#pragma once
#include "ECS.h"
#include "Link.h"
#include "Options.h"

class OptionsComponent : public Component
{
	int y_pos_, x_pos_, padding_;
	Vector2D alignment_;

	bool selection_made_ = false;
	OptionsData *data_;
	Options options_;
	Entity * target_;
	int options_id_;
public:
	SDL_Rect box;
	std::vector<std::vector<Link*>> current_links;
	SDL_Point position;

	explicit OptionsComponent(int options_id, int x, int y, Vector2D align, int pad);
	void init() override;
	void change_target(Entity * target);
	void next_x(int x_inc);
	void next_y(int y_inc);
	int get_path() const;
	Link * get_current_link();
	void make_selection();
};
