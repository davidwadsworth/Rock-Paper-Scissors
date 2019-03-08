#include "stdafx.h"
#include "LoadCharacterData.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>

CharacterCollection LoadCharacterData::load() const
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * characters_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	characters_node = data.first_node("Characters");
	auto character_collection = CharacterCollection();

	character_collection.id = characters_node->first_attribute("id")->value();
	
	for (auto character_node = characters_node->first_node("Character"); character_node; character_node = character_node->next_sibling())
	{
		auto character_data = CharacterData();
		character_data.id = character_node->first_attribute("id")->value();
		character_data.velocity =  atof(character_node->first_attribute("velocity")->value());
		character_data.hitbox = atof(character_node->first_attribute("hitbox")->value());


		for (auto attack_node = character_node->first_node("Attack"); attack_node; attack_node = attack_node->next_sibling())
		{
			auto attack_data = AttackData();
			attack_data.hitbox = atof(attack_node->first_attribute("hitbox")->value());
			attack_data.distance = atof(attack_node->first_attribute("distance")->value());
			character_data.attack_data.push_back(attack_data);
		}
		
		character_collection.data.push_back(character_data);
	}

	return character_collection;
}
