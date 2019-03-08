#pragma once
#include "LinkCommand.h"

class LinkStack
{
	std::vector<LinkCommand *> link_stack_;
	int link_cursor_;
public:
	LinkStack()
		: link_cursor_(0)
	{}

	~LinkStack()
	{
		link_stack_.clear();
	}

	 LinkCommand* get_last()
	 {
		if (link_stack_.size())
			return link_stack_[link_cursor_--];

		return nullptr;
	 }

	void add(LinkCommand * link)
	{
		if (link_stack_.size() == link_cursor_)
			link_stack_.push_back(link);
		else
			link_stack_[link_cursor_] = link;

		link_cursor_++;
	}

	void clear()
	{
		link_cursor_ = 0;
		link_stack_.clear();
	}

};
