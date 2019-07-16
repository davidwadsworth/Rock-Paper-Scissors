#pragma once
#include <vector>

/**
 * @author David Wadsworth
 */

struct AttackData
{
	int encoding = NULL;
	double hit_box = NULL;
	double distance = NULL;
	Uint32 move_stun = NULL;
	Uint32 hit_stun = NULL;
	int damage = NULL;
	int defense = NULL;
	int op_distance = NULL;
};

struct CharacterData
{
	std::string id;
	std::vector<AttackData> attack_data{};
	double velocity = NULL;
	double hit_box = NULL;
};

struct CharacterCollection : DataCollection
{
	std::vector<CharacterData> data{};
};