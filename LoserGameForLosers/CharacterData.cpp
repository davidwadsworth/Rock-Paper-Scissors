#include "stdafx.h"
#include "CharacterData.h"

std::vector<Character *> CharacterData::load()
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * characters_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	characters_node = data.first_node("Characters");

	std::vector<Character *> characters;
	
	for (rapidxml::xml_node<> * character_node = characters_node->first_node("Character"); character_node; character_node = character_node->next_sibling())
	{
		const char * id(character_node->first_attribute("id")->value());
		float velocity(atof(character_node->first_attribute("velocity")->value()));
		float hitbox(atof(character_node->first_attribute("hitbox")->value()));

		auto character_builder = new Character(id, velocity, hitbox);

		for (rapidxml::xml_node<> * attack_node = character_node->first_node("Attack"); attack_node; attack_node = attack_node->next_sibling())
		{
			float att_hitbox = atof(attack_node->first_attribute("hitbox")->value());
			float att_distance = atof(attack_node->first_attribute("distance")->value());
			character_builder->add_attack(att_hitbox, att_distance);
		}

		characters.push_back(character_builder);
	}

	return characters;
}
