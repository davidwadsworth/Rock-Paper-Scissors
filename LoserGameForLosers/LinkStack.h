#pragma once
#include "LinkCommand.h"

class LinkStack
{
	std::vector<LinkCommand *> links_;
	int top_;
public:
	LinkStack()
		: top_(0)
	{}

	~LinkStack()
	{
		links_.clear();
	}

	LinkCommand * peek()
	{
		if (is_empty())
			return nullptr;
		return links_[top_ - 1];
	}

	bool is_empty() const
	{
		return top_ == 0;
	}

	void push(LinkCommand * link)
	{
		top_++;
		links_.push_back(link);
	}

	LinkCommand* pop()
	{
		if (is_empty())
			return nullptr;

		const auto ret = links_[--top_];
		links_[top_] = nullptr;
		return ret;
	}


	void clear()
	{
		top_ = 0;
		links_.clear();
	}

};
