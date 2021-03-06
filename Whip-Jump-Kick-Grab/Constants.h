#pragma once
#include "SDL.h"
#include "Vector2D.h"

/**
 * @author David Wadsworth
 * 
 * static variables used throughout solution
 */

//inits
static const int SCREEN_HEIGHT = 640;
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;
static const int SCREEN_HALF_HEIGHT = SCREEN_HEIGHT / 2;

static const int FRAMES = 60;
static const int FRAME_DELAY = 1000 / FRAMES;

static const int ROTATION = 90;

static const int BACKGROUND_WIDTH = 800;
static const int BACKGROUND_HEIGHT = 640;
static const int BACKGROUND_Y_OFFSET = SCREEN_HEIGHT - BACKGROUND_HEIGHT;
static const int BACKGROUND_X_OFFSET = -BACKGROUND_WIDTH / 2 + SCREEN_HALF_WIDTH;

static const int CURSOR_WIDTH = 32;
static const int CURSOR_HEIGHT = 32;

static const int MAX_ARRAY_SIZE = 16;

static const int BOX_SIZE = 10;

static const int NUMBER_WIDTH = 100;
static const int NUMBER_HEIGHT = 160;

static const int PROMPT_DELAY = 3000;
static const int ROUND_TIME = 10000;
static const int TRANSITION_SPEED = 3;


//Runtime consts
static const double BACKGROUND_SCALING_TARGET = 1.0f;
static const double BACKGROUND_SCALING = 3.0f;
static const double SPRITE_SCALING = 3.0f;
static const double SPRITE_SCALING_TARGET = 1.0f;

static const double PLAYER_PRIORITY_INCREMENT = -0.3f;
static const int PLAYER_SPEED = 3;

static const int SPRITE_LENGTH = 128;
static const int SPRITE_SCALED = static_cast<int>(SPRITE_LENGTH * SPRITE_SCALING);
static const int SPRITE_RIGHT_EDGE_OF_SCREEN = SCREEN_WIDTH - SPRITE_SCALED;
static const int SPRITE_BOTTOM_OF_SCREEN = SCREEN_HEIGHT - SPRITE_SCALED;
static const int SPRITE_LEFT_EDGE_OF_SCREEN = 0;

static const int PLAYER_MAX_RANGE = 6;

static const int CURSOR_FREQUENCY = 30;

static const int BACKGROUND_COLLIDER = 2;
static const int RAND_CONSTANT = 1000;


static const int BAR_HEIGHT = 20;
static const int BAR_WIDTH = 337;
static const Vector2D BAR_POSITION_LEFT{ 58, 43 };
static const Vector2D BAR_POSITION_RIGHT{ 405, 43 };
static const int BAR_LEFT_CONTAINER_X = 25;
static const int BAR_LEFT_CONTAINER_Y = 0;
static const int BAR_RIGHT_CONTAINER_X = 400;
static const int BAR_RIGHT_CONTAINER_Y = 0;
static const int BAR_OFFSET = 58;

static const double HEALTH_TOTAL = 100.0;

static const int PADDING = 5;
static const int COMBAT_PADDING = 10;

static const Vector2D P1_OPTIONS = Vector2D(0, SCREEN_HALF_HEIGHT);
static const Vector2D P2_OPTIONS = Vector2D(SPRITE_RIGHT_EDGE_OF_SCREEN, SCREEN_HALF_HEIGHT );

//Attack consts
static const int ATTACK_LENGTH = 64;

static const double WHIP_RANGE = 0.8f;
static const double WHIP_DISTANCE = 0;
static const int WHIP_HEIGHT = 100;

static const double JUMP_KICK_RANGE = 0.3f;
static const double JUMP_KICK_DISTANCE = 1.0f;
static const int JUMP_KICK_HEIGHT = SPRITE_LENGTH - ATTACK_LENGTH;

static const double GRAB_RANGE = 0.3f;
static const double GRAB_DISTANCE = 0.1f;
static const int GRAB_HEIGHT = WHIP_HEIGHT;
static const int GRAB_ARM_SEPERATION = GRAB_HEIGHT + ATTACK_LENGTH + PADDING;


static const int ROUNDWIN = 3;
static const int ATTACK_DELAY = 1000;


// Enums
enum ANIMATIONS
{
	animation_player_idle,
	animation_player_walk_left,
	animation_player_walk_right,
	animation_player_block,
	animation_player_kick,
	animation_player_push,
	animation_player_hit,
	animation_player_whip,
	animation_player_jump_kick,
	animation_player_grab
};

enum FINAL_ATTACKS
{
	final_attack_whip,
	final_attack_Jump_Kick,
	final_attack_grab,
};

enum COMBAT_ATTACKS
{
	attack_nothing,
	attack_block,
	attack_kick,
	attack_push
};

enum CHARACTER_ATTACK_DATA
{
	character_order_attack_whip,
	character_order_attack_jump_kick,
	character_order_attack_grab,
	character_order_attack_block,
	character_order_attack_push,
	character_order_attack_kick
};

enum CHARACTER
{
	order_player_1,
	order_player_2
};

enum BACKGROUND
{
	background_cave
};

enum MAIN_SPRITESHEET
{
	ss_main_animations_blue_grab,
	ss_main_animations_blue_jump_kick,
	ss_main_animations_blue_whip,
	ss_main_animations_blue_block_1,
	ss_main_animations_blue_block_2,
	ss_main_animations_blue_block_3,
	ss_main_animations_blue_hit_1,
	ss_main_animations_blue_hit_2,
	ss_main_animations_blue_hit_3,
	ss_main_animations_blue_idle_1,
	ss_main_animations_blue_idle_2,
	ss_main_animations_blue_idle_3,
	ss_main_animations_blue_kick_1,
	ss_main_animations_blue_kick_2,
	ss_main_animations_blue_kick_3,
	ss_main_animations_blue_push_1,
	ss_main_animations_blue_push_2,
	ss_main_animations_blue_push_3,
	ss_main_animations_blue_walk_left_1,
	ss_main_animations_blue_walk_left_2,
	ss_main_animations_blue_walk_left_3,
	ss_main_animations_blue_walk_right_1,
	ss_main_animations_blue_walk_right_2,
	ss_main_animations_blue_walk_right_3,
	ss_main_animations_red_grab,
	ss_main_animations_red_jump_kick,
	ss_main_animations_red_whip,
	ss_main_animations_red_block_1,
	ss_main_animations_red_block_2,
	ss_main_animations_red_block_3,
	ss_main_animations_red_hit_1,
	ss_main_animations_red_hit_2,
	ss_main_animations_red_hit_3,
	ss_main_animations_red_idle_1,
	ss_main_animations_red_idle_2,
	ss_main_animations_red_idle_3,
	ss_main_animations_red_kick_1,
	ss_main_animations_red_kick_2,
	ss_main_animations_red_kick_3,
	ss_main_animations_red_push_1,
	ss_main_animations_red_push_2,
	ss_main_animations_red_push_3,
	ss_main_animations_red_walk_left_1,
	ss_main_animations_red_walk_left_2,
	ss_main_animations_red_walk_left_3,
	ss_main_animations_red_walk_right_1,
	ss_main_animations_red_walk_right_2,
	ss_main_animations_red_walk_right_3,
	ss_main_background_city,
	ss_main_cursor_box,
	ss_main_number_0,
	ss_main_number_1,
	ss_main_number_2,
	ss_main_number_3,
	ss_main_number_4,
	ss_main_number_5,
	ss_main_number_6,
	ss_main_number_7,
	ss_main_number_8,
	ss_main_number_9,
	ss_main_prompt_fight,
	ss_main_prompt_miss,
	ss_main_prompt_player_1_match_win,
	ss_main_prompt_player_1_wins,
	ss_main_prompt_player_2_match_win,
	ss_main_prompt_player_2_wins,
	ss_main_prompt_round,
	ss_main_prompt_select_attack,
	ss_main_prompt_stop,
	ss_main_health_bar,
	ss_main_health_container
};

enum COMBAT_TEX_ORDER
{
	order_texture_combat_ss_main,
	order_texture_combat_gray_background,
	order_texture_combat_glyph_atlas
};

enum MENU_TEX_ORDER
{
	order_texture_menu_ss_menu,
	order_texture_menu_white_background,
	order_texture_menu_glyph_atlas
};


enum MENU_SPRITESHEET
{
	ss_menu_cursor,
	ss_menu_how_to_play,
	ss_menu_title_screen
};

enum MUSIC_ORDER
{
	music_combat,
	music_drum_beat,
	music_title_theme,
	music_yamborghini_high
};

enum SOUND_ORDER
{
	sound_cymbal_swell,
	sound_hit_1,
	sound_hit_2,
	sound_hit_3,
	sound_miss,
	sound_swell_to_hit,
	sound_round_end,
	sound_blocking
};

enum CONTROLLER_DATA
{
	controller_combat_options,
	controller_menu_options,
	controller_back,
	controller_debug,
	controller_combat,
};

enum OPTIONS_DATA
{
	options_start_menu,
	options_choose_difficulty,
	options_choose_attack,
};

enum TEXTURE_ORDER
{
	texture_atlas_main,
	texture_white,	
	texture_glyph_atlas
};

enum INPUT_CONTROLLER_ORDER
{
	input_controller_player_1,
	input_controller_player_2,
	input_controller_player_1_single
};

enum DATA
{
	data_atlas,
	data_character,
	data_controller,
	data_options,
	data_audio,
};

enum FONTS
{
	font_lazy_foo
};