#pragma once
#include "Navigator.h"
#include "CommonNavigation.h"
#include "AttackPresets.h"
#include "CombatPresets.h"
namespace AttackPresets
{
	class KickHitStun;
	class PlayerSlideBack;
}

namespace InputCommands
{
	class Move;
}

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
	class CombatCollision final : public Navigator
	{
		Entity * player_1_, *player_2_;
	public:
		CombatCollision(Entity * player_1, Entity * player_2);
		int choose_path() override;
	};

	/**
	 * Moves player incrementally until it reaches a desired distance
	 */
	class MovePlayer : public Navigator
	{
		Entity * player_;
		int distance_moved_, total_distance_;
		InputCommands::Move * move_, *stop_;
	public:
		MovePlayer(Entity * player, int distance_move);
		int choose_path() override;
		void close() override;
	};

	/**
	 * Moves player incrementally until it reaches a desired distance or collides with a specified entity
	 */
	class MovePlayerToCollision : public MovePlayer
	{
		Entity * player_, *other_;
	public:
		MovePlayerToCollision(Entity * player, Entity * other, int distance_move);
		int choose_path() override;
	};

	class ResetVelocity : public Navigator
	{
		InputCommands::Move * stop_;
		Entity * player_;
	public:
		ResetVelocity(Entity * player);
		int choose_path() override;
	};

	/*
	 * animates the player in a pushing state and moves the other player and deals damage, unless he is blocking which makes the move do nothing
	 */
	class PushPlayer : public Delay
	{
		Entity * attacker_, * victim_;
		AttackPresets::PlayerSlideBack * slide_back_;
		InputCommands::Move * move_;
		bool used_;
	public:
		PushPlayer(Entity * attacker, Entity * victim, Uint32 attack_frames);

		void init() override;
		int choose_path() override;
		void close() override;
	};


	/*
	 * animates the player in a kicking state and deals damage to the other player, unless he is blocking which deals reduced damage
	 */
	class KickPlayer : public Delay
	{
		Entity * attacker_, * victim_;
		AttackPresets::KickHitStun* stun_;
		InputCommands::Move * move_;
		bool used_;
	public:
		KickPlayer(Entity * attacker, Entity * victim, Uint32 attack_frames);

		void init() override;
		int choose_path() override;
		void close() override;
	};

	/*
	 * animates the player in a blocking state
	 */
	class BlockPlayer : public Delay
	{
		Entity * blocker_;
		InputCommands::Move * move_;
		bool used_;
	public:
		BlockPlayer(Entity * blocker, Uint32 block_frames);

		void init() override;
		int choose_path() override;
		void close() override;
	};

	/**
	 * sets the character to single static image among the loaded animations
	 */
	class SetAnimation : public Navigator
	{	
		Entity * player_;
		int animation_, animation_pos_;
	public:
		SetAnimation(Entity * player, int animation, int animation_pos);
		int choose_path() override;
	};

	class ExecuteFinalAttack : public Navigator
	{
		Entity * player_;
		int animation_, animation_pos_;
	public:
		ExecuteFinalAttack(Entity * player, int animation, int animation_pos);
		int choose_path() override;
	};

	/**
	 * Resets the character back to idle
	 */
	class ResetAnimations : public Navigator
	{
		Entity* player_;
	public:
		ResetAnimations(Entity * player);
		int choose_path() override;
	};

	/**
	 * subtracts damage from the character
	 */
	class ReceiveDamage : public Navigator
	{
		int player_;
		Entity* overlay_;
		int damage_;
	public:
		ReceiveDamage(int player, int damage);
		void init() override;
		int choose_path() override;
	};

	/**
	 * checks to see if the round is over, and if so loads the end of game sequence and transition to the main menu
	 */
	class CheckRoundLoss : public Navigator
	{
		int player_;
		Entity * overlay_;
		CombatPresets::MatchEnding* match_end_;
	public:
		CheckRoundLoss(int player);

		void init() override;
		int choose_path() override;
		void close() override;
	};

	/**
	 * checks to see if the two players are colliding
	 */
	class CheckCollision : public Navigator
	{
		Entity * player_1_, *player_2_;
	public:
		CheckCollision(Entity * player_1, Entity * player_2);
		int choose_path() override;
	};

	/**
	 * plays a locked animation
	 */
	class LockedAnimation : public Navigator
	{
		Entity * player_;
		int animation_;
	public:
		LockedAnimation(Entity * player, int animation);
		void init() override;
		int choose_path() override;
	};

	/**
	 * checks each players chosen attack and decides the round winner
	 */
	class CheckWinner : public Navigator
	{
		Entity * player_1_, * player_2_,* priority_,* other_;
	public:
		CheckWinner(Entity * player_1, Entity * player_2);
		void init() override;
		int choose_path() override;
	};

	/**
	 * checks if the player has priority or not
	 */
	class CheckPriority : public Navigator
	{
		Entity * player_;
	public:
		CheckPriority(Entity * player);
		int choose_path() override;
	};

	class SwapPriority : public Navigator
	{
		Entity * player_1_, * player_2_;
	public:
		SwapPriority(Entity * player_1, Entity * player_2);
		int choose_path() override;
	};

	class ClearPath : public Navigator
	{
		Entity * player_;
	public:
		ClearPath(Entity * player);
		int choose_path() override;
	};
}


