#include "stdafx.h"
#include "Pathway.h"

PathTrunk::PathTrunk(PathBranch * root, PathTrunk * next)
	: root_(root), current(root), next(next)
{}

void PathTrunk::add(PathTrunk * trunk_to_add)
{
	trunk_to_add->next = next;
	next = trunk_to_add;
}

bool PathTrunk::has_next() const
{
	return next;
}

bool PathTrunk::has_current() const
{
	return current;
}

void post_order_delete(PathBranch * branch)
{
	if (branch == nullptr) return;
	post_order_delete(branch->child);
	post_order_delete(branch->sibling);
	branch->remove();
}

void PathTrunk::remove() const
{
	post_order_delete(root_);
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
	for (auto& n : navigators_) n.reset();
	child = nullptr;
	sibling = nullptr;
	parent = nullptr;
	previous = nullptr;
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
		if (has_child())
			child->previous = parent->current;
		parent->current = child;
		break;
	default: // chooses a new path, if it exists
		if (has_sibling())
		{
			auto temp_sibling = sibling;
			for (auto i = 2; i < path && temp_sibling; i++)
				temp_sibling = temp_sibling->sibling;

			temp_sibling->previous = parent->current;
			parent->current = temp_sibling;
		}
		else
		{
			if (has_child())
				child->previous = parent->current;
			parent->current = child;
		}
		break;
	}
}


