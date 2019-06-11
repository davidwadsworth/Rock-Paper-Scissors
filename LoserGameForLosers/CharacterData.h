#pragma once
#include <vector>

struct AttackData
{
	int encoding;
	float hit_box;
	float distance;
	Uint32 move_stun;
	Uint32 hit_stun;
	int damage;
	int defense;
	float op_distance;
};

struct CharacterData
{
	std::string id;
	std::vector<AttackData> attack_data;
	float velocity;
	float hit_box;
};

struct CharacterCollection : DataCollection
{
	std::vector<CharacterData> data;
};