#include "stdafx.h"
#include "LoadCharacterData.h"
#include <rapidxml.hpp>
#include <fstream>
#include <vector>

CharacterCollection LoadCharacterData::load() const
{
	std::ifstream character_path(path);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * characters_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	characters_node = data.first_node("Characters");
	auto character_collection = CharacterCollection();
	character_collection.id = characters_node->first_attribute("id")->value();
	character_collection.path = characters_node->first_attribute("path")->value();
	
	for (auto character_node = characters_node->first_node("Character"); character_node; character_node = character_node->next_sibling())
	{
		auto character_data = CharacterData();
		character_data.id = character_node->first_attribute("id")->value();
		character_data.velocity =  atof(character_node->first_attribute("velocity")->value());
		character_data.hit_box = atof(character_node->first_attribute("hitbox")->value());


		for (auto attack_node = character_node->first_node("Attack"); attack_node; attack_node = attack_node->next_sibling())
		{
			auto attack_data = AttackData();
			attack_data.encoding = atoi(attack_node->first_attribute("encoding")->value());
			attack_data.hit_box = atof(attack_node->first_attribute("hitbox")->value());

			if (attack_node->first_attribute("distance"))
				attack_data.distance = atof(attack_node->first_attribute("distance")->value());

			if (attack_node->first_attribute("move_stun"))
				attack_data.move_stun = atoi(attack_node->first_attribute("move_stun")->value());

			if (attack_node->first_attribute("hit_stun"))
				attack_data.hit_stun = atoi(attack_node->first_attribute("hit_stun")->value());

			if (attack_node->first_attribute("damage"))
				attack_data.damage = atoi(attack_node->first_attribute("damage")->value());

			if (attack_node->first_attribute("defense"))
				attack_data.defense = atoi(attack_node->first_attribute("defense")->value());

			if (attack_node->first_attribute("op_distance"))
				attack_data.op_distance = atoi(attack_node->first_attribute("op_distance")->value());

			character_data.attack_data.push_back(attack_data);
		}
		
		character_collection.data.push_back(character_data);
	}

	data.clear();
	return character_collection;
}
