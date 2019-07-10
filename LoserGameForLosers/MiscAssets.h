#pragma once
#include "Asset.h"

namespace Assets
{
	class PlayerLeft : public Asset
	{
	public:
		PlayerLeft(Manager* manager)
			: Asset(manager)
		{}
		void create(int controller_id);
		void destroy() override;
	};

	class PlayerRight : public Asset
	{
	public:
		PlayerRight(Manager* manager)
			: Asset(manager)
		{}

		void create(int controller_id, int difficulty);
		void destroy() override;
	};

	class CombatBackground : public Asset
	{
	public:
		CombatBackground(Manager* manager)
			: Asset(manager)
		{}

		void create();
		void destroy() override;
	};

	class OptionBox : public Asset
	{
	public:
		OptionBox(Manager * manager)
			: Asset(manager)
		{}

		void create(int glyph_id, int cursor_id, int options_id, int controller_id, Vector2D position, int input_id);
		void destroy() override;
	};

	class Prompt : public Asset
	{
	public:
		Prompt(Manager * manager)
			: Asset(manager)
		{}

		void create(int sprite_id, SDL_Rect * position);
		void destroy() override;
	};

	class MenuScreen : public Asset
	{
	public:
		MenuScreen(Manager * manager)
			: Asset(manager)
		{}

		void create();
		void destroy() override;
	};

	class Back : public Asset
	{
	public:
		Back(Manager * manager)
			: Asset(manager)
		{}

		void create();
		void destroy() override;
	};

	class Transition : public Asset
	{
	public:
		Transition(Manager * manager)
			: Asset(manager)
		{}
		void create(int frames, int texture_id);
		void destroy() override;
	};

	class Overlay : public Asset
	{
	public:
		Overlay(Manager* manager)
			: Asset(manager)
		{}

		void create(int container_id, int bar_id, SDL_RendererFlip flip);
		void destroy() override;
	};
}
