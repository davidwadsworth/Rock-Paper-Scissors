#pragma once
#include <vector>

struct AttackData
{
	float hitbox;
	float distance;
};

struct CharacterData
{
	std::string id;
	std::vector<AttackData> attack_data;
	float velocity;
	float hitbox;
};

struct CharacterCollection : DataCollection
{
	std::vector<CharacterData> data;
};