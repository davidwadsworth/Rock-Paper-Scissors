#pragma once
#include "Navigator.h"
#include "ECS.h"

/**
 * @author David Wadsworth
 * 
 * in charge of menu navigation
 */

namespace Navigation
{

	class ChangeScreen : public Navigator
	{
		int screen_id_;
		Entity * screen_;
		Assets::Back * back_;
	public:
		ChangeScreen(Entity * screen, int screen_id)
			: screen_id_(screen_id), screen_(screen), back_(nullptr)
		{}

		void init() override;
		void close() override;
		int choose_path() override;
	};
}