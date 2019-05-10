#include "Navigator.h"
#include "Components.h"

namespace Navigation
{
	/**
	 * resets players and backgrounds position and scaling to their initial values
	 */
	class ResetPlayersAndBackground final : public Navigator
	{
		Entity * player_1_, *player_2_, *background_;
	public:
		ResetPlayersAndBackground(Entity * player1, Entity * player2, Entity * background);
		int choose_path() override;
	};

	/**
	 * Using AABB collision. Moves the position of the players in the direction of the slower player
	 */
	class CheckCollision final : public Navigator
	{
		Entity * player_1_, * player_2_;
	public:
		CheckCollision(Entity * player_1, Entity * player_2);
		int choose_path() override;
	};

	/**
	 * Moves player x to player y
	 */
	class MovePlayerToOtherPlayer final : public Navigator
	{
		Entity * moving_, *comparing_;
		InputCommands::Move move_command_;
		float velocity_, distance_left_, distance_;
	public:
		MovePlayerToOtherPlayer(Entity * player_to_move, Entity * other_player, float distance);
		void init() override;
		int choose_path() override;

	};

	/**
	 * returns the winner of two players accounting for attack distance and the rock paper scissors winner determinant located in PlayerComponent
	 */
	class CheckAttackWinner : public Navigator
	{
		Entity * priority_, *other_;
		bool attack_used_;
	public:
		CheckAttackWinner(Entity * priority, Entity * other, bool attack_used);

		int choose_path() override;

	};

	/**
	 * Background scales and scrolls based on player position (for more info see Background.h)
	 */
	class ScalingScrollingBackground : public Navigator
	{
		Background* moving_background_;
		Entity * player_1_, *player_2_, *background_;
	public:
		ScalingScrollingBackground(Entity * player_1, Entity* player_2, Entity * background);
		void init() override;
		int choose_path() override;
		void close() override;

	};

	/**
	 * Creates a lingering attack projectile from AssetManager that destroys itself once the distance is reached or it hits its target
	 */
	class CreateAttack : public Navigator
	{
		Entity * player_, * attack_;
	public:
		explicit CreateAttack(Entity * player);

		void init() override;
		int choose_path() override;
		void close() override;
	};
}


