#include "Pathway.h"

class PathQueue
{
	class Node
	{
	public:
		Pathway * data;
		Node * next = nullptr;

		Node()
			: data(nullptr)
		{}

		explicit Node(Pathway * process)
			: data(process)
		{}
	};

	int active_queue_size_;
	int pending_queue_size_;

	Node * active_queue_head_;
	Node * pending_queue_head_;
public:

	PathQueue()
	{}

	~PathQueue()
	{
		active_queue_head_->next = nullptr;
		pending_queue_head_->next = nullptr;
	}

	void queue_path(Pathway * path)
	{
		
	}


};