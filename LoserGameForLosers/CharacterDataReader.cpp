#include "stdafx.h"
#include "CharacterDataReader.h"

CharacterDataReader::CharacterDataReader()
{
}

Character * CharacterDataReader::load(CHARACTER character, const char * path)
{
	int srcX, srcY, scaledX, scaledY, rotations, tileID;
	float velocity, hitbox;
	std::string id;

	std::ifstream character_path(path);
	rapidxml::xml_document<> map;
	rapidxml::xml_node<> * root_node;
	const char * layerName;
	const char * tileName;
	const char * flipx;

	std::vector<char> buffer((std::istreambuf_iterator<char>(character_path)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	map.parse<0>(&buffer[0]);

	root_node = map.first_node("Characters");



	auto character_node = &root_node[character];

	auto character_builder = new Character()




	for (rapidxml::xml_node<> * layer_node = &root_node[character]; layer_node; layer_node = layer_node->next_sibling();)
	{
		
	}


	return nullptr;
}
