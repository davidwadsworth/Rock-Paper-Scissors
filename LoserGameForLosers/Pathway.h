#pragma once
#include "Navigator.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class PathBranch;

class PathTrunk
{
	PathBranch * root_;
	bool active_;
public:
	PathTrunk() = default;
	PathTrunk(PathBranch * root, PathTrunk * next);

	void add(PathTrunk * trunk_to_add);
	void remove() const;
	bool has_next() const;
	bool has_current() const;

	PathTrunk * next;
	PathBranch * current;
};

using NavigatorID = std::size_t;

inline NavigatorID getNewNavigatorTypeID()
{
	static NavigatorID last_id = 0u;
	return last_id++;
}

template <typename T> inline NavigatorID getNavigatorTypeID() noexcept
{
	static_assert (std::is_base_of<Navigator, T>::value, "");
	static NavigatorID type_id = getNewComponentTypeID();
	return type_id;
}

constexpr std::size_t maxNavigators = 32;
using NavigatorBitSet = std::bitset<maxNavigators>;
using NavigatorArray = std::array<Navigator*, maxNavigators>;

class PathBranch
{
	std::vector<std::unique_ptr<Navigator>> navigators_;
	NavigatorArray navigator_array_;
	NavigatorBitSet navigator_bit_set_;
public:
	PathBranch() = default;
	PathBranch(PathTrunk * parent, PathBranch * sibling, PathBranch * child);

	bool has_child() const { return child; }
	bool has_sibling() const { return sibling; }
	bool has_previous() const { return previous; }

	void init();
	//
	void close();
	void remove();

	PathTrunk * parent = nullptr;
	PathBranch * previous = nullptr;
	PathBranch * sibling = nullptr;
	PathBranch * child = nullptr;

	template <typename T> bool has_navigator() const
	{
		return navigator_bit_set_[getNavigatorTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& add_navigator(TArgs&&... m_args)
	{
		T* n(new T(std::forward<TArgs>(m_args)...));
		n->branch = this;
		std::unique_ptr<Navigator> u_ptr{ n };
		navigators_.emplace_back(std::move(u_ptr));

		navigator_array_[getNavigatorTypeID<T>()] = n;
		navigator_bit_set_[getNavigatorTypeID<T>()] = true;

		n->init();
		return *n;
	}

	template<typename T> T& get_navigator() const
	{
		auto ptr(navigator_array_[getNavigatorTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	void navigate_path() const;
};

class Path
{
	PathTrunk * head_;
public:

	Path() = default;

	~Path()
	{
		head_ = new PathTrunk();
	}

	void add(PathTrunk * trunk) const
	{
		head_->add(trunk);
	}

	void previous_path() const
	{
		if (head_->current->has_previous())
		{
			head_->current = head_->current->previous;
		}
	}

	void navigate_path()
	{
		if (head_->has_current())
			head_->current->navigate_path();
		else
			if(head_->has_next())
			{
				const auto current_head = head_;
				head_ = current_head->next;
				current_head->remove();
				current_head->next = nullptr;
			}
	}

};
