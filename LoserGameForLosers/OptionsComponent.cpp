#include "stdafx.h"

void OptionsComponent::change_options(const int new_options)
{
	options_id = new_options;
	options_ = Options(Game::data->get_options_data(this->options_id));
	current_links = options_.build_options(position.x, position.y, alignment_, padding_);
	box = options_.box;
	x_pos_ = 0;
	y_pos_ = 0;
	entity->get_component<GlyphAtlasComponent>().create_labels();
	entity->get_component<WhiteRectComponent>().set_rect();
}
