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

void release_ptr_rec(PathBranch* branch)
{
	if (!branch)
		return;

	release_ptr_rec(branch->child);
	release_ptr_rec(branch->sibling);
	branch->remove();
}

void PathTrunk::remove()
{
	release_ptr_rec(root_);
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
	: navigator_array_(), parent(parent), sibling(sibling), child(child)
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
	for (auto& n : navigators_) n.release();
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
		else
		{
			parent->current->close();
			if (has_child())
			{
				child->previous = parent->current;
				child->init();
			}
			parent->current = child;
		}
		break;
	}
}


