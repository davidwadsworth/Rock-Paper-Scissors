#pragma once
#include "Navigator.h"
#include "Components.h"
#include "CommonNavigation.h"
#include "Navigator.h"
#include "Components.h"
#include "CommonNavigation.h"
#include "AttackQueue.h"
#include "AttackPresets.h"

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
		Entity * player_1_, * player_2_;
	public:
		CombatCollision(Entity * player_1, Entity * player_2);
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
	class ConvergeTowardsOtherPlayer final : public Navigator
	{
		Entity * moving_, *comparing_;
		InputCommands::Move move_command_;
		float velocity_, distance_left_, distance_;
	public:
		ConvergeTowardsOtherPlayer(Entity * player_to_move, Entity * other_player, float distance);
		void init() override;
		int choose_path() override;

	};

	class RepelFromOtherPlayer final : public Navigator
	{
		Entity * moving_, *comparing_;
		InputCommands::Move move_command_;
		float velocity_, distance_left_, distance_;
	public:
		RepelFromOtherPlayer(Entity * player_to_move, Entity * other_player, float distance);
		void init() override;
		int choose_path() override;

	};

	class MovePlayer final : public Navigator
	{
		
	};


	class PushPlayer : public Delay
	{
		Entity * player_, * other_player_;
		AttackPresets::PlayerSlideBack slide_back_;
		bool used_;
	public:
		PushPlayer(Entity * player, Entity *other_player, Uint32 attack_frames);
		AttackQueue * other_player_queue_;
		AttackPresets::PlayerSlideBack slide_back_;
		bool used_;
	public:
		PushPlayer(Entity * player, Entity *other_player, AttackQueue * other_player_queue, Uint32 attack_frames);

		void init() override;
		int choose_path() override;
		void close() override;

	};

	class KickPlayer : public Delay
	{
		Entity * player_, *other_player_;
		AttackPresets::KickHitStun stun_;
		bool used_;
	public:
		KickPlayer(Entity * player, Entity *other_player, Uint32 attack_frames);
		AttackQueue * other_player_queue_;
		AttackPresets::KickHitStun stun_;
		bool used_;
	public:
		KickPlayer(Entity * player, Entity *other_player, AttackQueue * other_player_queue, Uint32 attack_frames);

		void init() override;
		int choose_path() override;
		void close() override;
	};

	class BlockPlayer : public Delay
	{
		Entity * player_;
		bool used_;
	public:
		BlockPlayer(Entity * player, Uint32 attack_frames);

		void init() override;
		int choose_path() override;
		void close() override;
	};

	class SetAnimation : public Navigator
	{
		
	};

	class ResetAnimations : public Navigator
	{
		
	};

	class ReceiveDamage : public Navigator
	{};

	class CheckRoundLoss : public Navigator
	{
	};

	class DealDamage : public Navigator
	{};

	class CheckCollision : public Navigator
	{};

	class LockedAnimation : public Navigator
	{};

	class CheckWinner : public Navigator
	{};

	class CheckPriority : public Navigator
	{};

}


