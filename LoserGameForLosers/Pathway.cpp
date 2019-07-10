#include "stdafx.h"
#include "Pathway.h"


PathTrunk::PathTrunk(PathBranch * root, PathTrunk * next)
	: root_(root), next(next), current(root)
{}


void PathTrunk::add(PathTrunk * trunk_to_add)
{
	trunk_to_add->next = next;
	next = trunk_to_add;
}

void PathTrunk::reset()
{
	current = root_;
}


void post_order_remove(PathBranch * branch)
{
	if (!branch)
		return;

	post_order_remove(branch->child);
	post_order_remove(branch->sibling);
	branch->remove();
}

void PathTrunk::remove() const
{
	post_order_remove(root_);
}


bool PathTrunk::has_next() const
{
	return next;
}

bool PathTrunk::has_current() const
{
	return current;
}

PathBranch::PathBranch(PathTrunk * parent, PathBranch * sibling, PathBranch * child)
	: parent(parent), sibling(sibling), child(child)
{}

void PathBranch::init()
{
	for (auto& n : navigators_) n->init();
}

void PathBranch::close()
{
	for (auto& n : navigators_) n->close();
}

void PathBranch::remove()
{
	navigators_.clear();
}

void PathBranch::navigate_path() const
{
	auto path = 0;
	for (auto& nav : navigators_)
	{
		const auto path_result = nav->choose_path();
		path = path_result != 0 ? path_result : 0;
	}

	switch (path)
	{
	case 0: // stay on same path
		break;
	case 1: // continue on this path
		parent->current->close();
		if (has_child())
		{
			child->previous = parent->current;
			child->init();
		}	
		parent->current = child;
		break;
	default: // chooses a new path, if it exists
		if (has_sibling())
		{
			parent->current->close();
			auto temp_sibling = sibling;
			for (auto i = 2; i < path && temp_sibling; i++)
				temp_sibling = temp_sibling->sibling;

			temp_sibling->previous = parent->current;
			parent->current = temp_sibling;
			parent->current->init();
		}
		break;
	}
}