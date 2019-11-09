#pragma once
#include "Navigator.h"
#include <vector>

/**
 * @author David Wadsworth
 *
 * using the Tree pattern creates the outline for which patterns can be loaded in and using "Navigation" goes through the tree using pathway decisions on runtime
 * 
 * Used by GameState and ScriptComponent.
*/

class PathTrunk
{
	PathBranch * root_;
	bool active_;
public:
	PathTrunk() = default;
	PathTrunk(PathBranch * root, PathTrunk * next);

	void add(PathTrunk * trunk_to_add);
	void reset();
	void remove() const;
	bool has_next() const;
	bool has_current() const;

	PathTrunk * next;
	PathBranch * current;
};



class PathBranch
{
	std::vector<Navigator*> navigators_;
public:
	PathBranch() = default;
	PathBranch(PathTrunk * parent, PathBranch * sibling, PathBranch * child);

	bool has_child() const { return child; }
	bool has_sibling() const { return sibling; }
	bool has_previous() const { return previous; }

	void init();
	void close();

	PathTrunk * parent = nullptr;
	PathBranch * previous = nullptr;
	PathBranch * sibling = nullptr;
	PathBranch * child = nullptr;


	void add_navigator(Navigator * nav)
	{
		navigators_.push_back(nav);
	}

	void remove();

	void navigate_path() const;
};



class Path
{
	PathTrunk * head_;
public:

	Path()
		: head_(nullptr)
	{}

	virtual ~Path()
	{
		if (head_)
			head_->remove();
		head_ = nullptr;
	}

	PathTrunk* get_head() const { return head_; }
	void set_head(PathTrunk * head) { head_ = head; }

	virtual bool is_empty() const
	{
		return !head_;
	}

	virtual void clear()
	{
		if (head_)
			if (head_->has_current())
			{
				head_->current->close();
				head_->current = nullptr;
			}

		head_ = nullptr;
	}

	virtual void add(PathTrunk * trunk)
	{
		if (head_)
			head_->add(trunk);
		else
		{
			head_ = trunk;
			head_->current->init();
		}
	}

	virtual void previous_path() const
	{
		if (head_->current->has_previous())
		{
			head_->current->close();
			head_->current = head_->current->previous;
			head_->current->init();
		}
	}

	virtual void navigate_path()
	{

		if (!head_)
			return;

		if (head_->has_current())
			head_->current->navigate_path();
		else
		{
			head_ = head_->next;
			if (head_)
				head_->current->init();
		}
	}

};

