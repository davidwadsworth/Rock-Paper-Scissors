#include "stdafx.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>
#include "LoadAtlasData.h"

AtlasCollection LoadAtlasData::load()
{
	xml_path.open(path);

	buffer.assign(std::istreambuf_iterator<char>(xml_path), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	const auto texture_atlas_node = data.first_node("TextureAtlas");

	atlas_collection_.id = texture_atlas_node->first_attribute("id")->value();
	atlas_collection_.path = texture_atlas_node->first_attribute("imagePath")->value();
	atlas_collection_.image_width = atoi(texture_atlas_node->first_attribute("width")->value());
	atlas_collection_.image_height = atoi(texture_atlas_node->first_attribute("height")->value());
	atlas_collection_.texture_id = atoi(texture_atlas_node->first_attribute("textureID")->value());

	for (auto sprite_node = texture_atlas_node->first_node("sprite"); sprite_node; sprite_node = sprite_node->next_sibling())
	{
		auto atlas_data = AtlasData();

		atlas_data.texture_id = atlas_collection_.texture_id;
		atlas_data.n = sprite_node->first_attribute("n")->value();
		atlas_data.x = atoi(sprite_node->first_attribute("x")->value());
		atlas_data.y = atoi(sprite_node->first_attribute("y")->value());
		atlas_data.w = atlas_data.original_w = atoi(sprite_node->first_attribute("w")->value());
		atlas_data.h = atlas_data.original_h = atoi(sprite_node->first_attribute("h")->value());

		if (sprite_node->first_attribute("oX"))
		{
			atlas_data.offset_x = atoi(sprite_node->first_attribute("oX")->value());
			atlas_data.offset_y = atoi(sprite_node->first_attribute("oY")->value());
			atlas_data.original_w = atoi(sprite_node->first_attribute("oW")->value());
			atlas_data.original_h = atoi(sprite_node->first_attribute("oH")->value());
		}

		if (sprite_node->first_attribute("r"))
		{
			atlas_data.is_rotated = true;
		}

		atlas_collection_.data.push_back(atlas_data);
	}

	data.clear();
	return atlas_collection_;
}

const char * LoadAtlasData::image_source()
{
	xml_path.open(path);

	buffer.assign((std::istreambuf_iterator<char>(xml_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	data.clear();
	return data.first_node("TextureAtlas")->first_attribute("imagePath")->value();
}
