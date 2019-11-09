#pragma once
#include "DataCollection.h"


class AIData
{
public:
	std::string id;
	int block_rand_range;
	int kick_rand_range;
	int push_rand_range;
	double block_range;
	double kick_range;
	double push_range;
	int move_left_range_min;
	int move_left_range_max;
	int move_right_range_min;
	int move_right_range_max;
	int block_range_min;
	int block_range_max;
};

class AICollection : public DataCollection
{
public:
	std::vector<AIData> data;
};

