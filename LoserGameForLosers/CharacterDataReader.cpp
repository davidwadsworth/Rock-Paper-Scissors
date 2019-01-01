#include "stdafx.h"
#include "CharacterDataReader.h"

Character * CharacterDataReader::load(int char_id)
{
	std::ifstream character_path(path_);
	rapidxml::xml_document<> data;
	rapidxml::xml_node<> * root_node;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	data.parse<0>(&buffer[0]);

	root_node = data.first_node("Characters");

	int xml_pos = 0;

	Character * character_builder = new Character();
	
	for (rapidxml::xml_node<> * character_node = root_node->first_node("Character"); character_node; character_node = character_node->next_sibling())
	{
		if (xml_pos == char_id)
		{
			const char * id(character_node->first_attribute("id")->value());
			float velocity(atof(character_node->first_attribute("velocity")->value()));
			float hitbox(atof(character_node->first_attribute("hitbox")->value()));

			character_builder = new Character(id, velocity, hitbox);

			for (rapidxml::xml_node<> * attack_node = character_node->first_node("Attack"); attack_node; attack_node = attack_node->next_sibling())
			{
				float att_hitbox = atof(attack_node->first_attribute("hitbox")->value());
				float att_distance = atof(attack_node->first_attribute("distance")->value());
				character_builder->add_attack(att_hitbox, att_distance);
			}
		}
		xml_pos++;
	}

	return character_builder;
}
