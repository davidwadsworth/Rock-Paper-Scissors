#pragma once
#include "Pathway.h"


class AttackQueue
{
	Path path_;
public:
	AttackQueue()
	{
		path_ = Path();
	}
	~AttackQueue() = default;

	void empty_add(PathTrunk * action)
	{
		if (path_.is_empty())
			path_.add(action);
	}

	void clear_add(PathTrunk * action)
	{
		path_.clear();
		path_.add(action);
	}

	void add(PathTrunk * action)
	{
		path_.add(action);
	}

};
