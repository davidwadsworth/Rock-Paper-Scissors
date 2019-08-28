#include "stdafx.h"
#include "AIData.h"
#include "LoadAIData.h"

AICollection LoadAIData::load()
{
	xml_path.open(path);

	buffer.assign(std::istreambuf_iterator<char>(xml_path), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	const auto ai_node = data.first_node("AI");

	ai_collection_.id = ai_node->first_attribute("id")->value();
	ai_collection_.path = ai_node->first_attribute("path")->value();

	for (auto bot_node = ai_node->first_node("Bot"); bot_node; bot_node = bot_node->next_sibling())
	{
		auto ai_data = AIData();

		ai_data.id = bot_node->first_attribute("id")->value();
		ai_data.block_rand_range = atoi(bot_node->first_attribute("block_rand_range")->value());
		ai_data.kick_rand_range = atoi(bot_node->first_attribute("kick_rand_range")->value());
		ai_data.push_rand_range = atoi(bot_node->first_attribute("push_rand_range")->value());
		ai_data.block_range = atof(bot_node->first_attribute("block_range")->value());
		ai_data.kick_range = atof(bot_node->first_attribute("kick_range")->value());
		ai_data.push_range = atof(bot_node->first_attribute("push_range")->value());
		ai_data.move_left_range_min = atoi(bot_node->first_attribute("move_left_range_min")->value());
		ai_data.move_left_range_max = atoi(bot_node->first_attribute("move_left_range_max")->value());
		ai_data.move_right_range_min = atoi(bot_node->first_attribute("move_right_range_min")->value());
		ai_data.move_right_range_max = atoi(bot_node->first_attribute("move_right_range_max")->value());
		ai_data.block_range_min = atoi(bot_node->first_attribute("block_range_min")->value());
		ai_data.block_range_max = atoi(bot_node->first_attribute("block_range_max")->value());

		ai_collection_.data.push_back(ai_data);
	}

	data.clear();
	return ai_collection_;
}
