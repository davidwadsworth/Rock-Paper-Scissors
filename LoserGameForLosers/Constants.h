#pragma once
#include "SDL.h"
#include "Vector2D.h"

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

//Runtime consts
static const float BACKGROUND_SCALING_TARGET = 1.0f;
static const float BACKGROUND_SCALING = 3.0f;
static const float SPRITE_SCALING = 3.0f;
static const float SPRITE_SCALING_TARGET = 1.0f;

static const float PLAYER_PRIORITY_INCREMENT = -0.3f;
static const int PLAYER_SPEED = 3;

static const int SPRITE_LENGTH = 128;
static const int SPRITE_SCALED = SPRITE_LENGTH * SPRITE_SCALING;
static const int SPRITE_RIGHT_EDGE_OF_SCREEN = SCREEN_WIDTH - SPRITE_SCALED;
static const int SPRITE_BOTTOM_OF_SCREEN = SCREEN_HEIGHT - SPRITE_SCALED;
static const int SPRITE_LEFT_EDGE_OF_SCREEN = 0;

static const int PLAYER_MAX_RANGE = 6;

static const int CURSOR_FREQUENCY = 30;
static const int ROUND_TIME = 4;
static const int SELECT_ATTACK_TIME = 3;

static const float SQUARE_VELOCITY = 0.6;
static const float ARMS_VELOCITY = 1.0;

static const int BACKGROUND_COLLIDER = 2;

static const int PADDING = 5;

static const Vector2D P1_OPTIONS = Vector2D(0, SCREEN_HALF_HEIGHT);
static const Vector2D P2_OPTIONS = Vector2D(SPRITE_RIGHT_EDGE_OF_SCREEN, SCREEN_HALF_HEIGHT );

//Attack consts
static const int ATTACK_LENGTH = 64;

static const float WHIP_RANGE = 0.8f;
static const float WHIP_DISTANCE = 0;
static const int WHIP_HEIGHT = 100;

static const float JUMP_KICK_RANGE = 0.3f;
static const float JUMP_KICK_DISTANCE = 1.0f;
static const int JUMP_KICK_HEIGHT = SPRITE_LENGTH - ATTACK_LENGTH;

static const float GRAB_RANGE = 0.3f;
static const float GRAB_DISTANCE = 0.1f;
static const int GRAB_HEIGHT = WHIP_HEIGHT;
static const int GRAB_ARM_SEPERATION = GRAB_HEIGHT + ATTACK_LENGTH + PADDING;


static const int ROUNDWIN = 3;


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
	character_order_attack_kick,
	character_order_attack_push
};

enum CHARACTER
{
	player_blue,
	player_red
};

enum BACKGROUND
{
	cave
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
	ss_main_attacks_blue_grab_extension,
	ss_main_attacks_blue_grab_hit,
	ss_main_attacks_blue_grab_miss,
	ss_main_attacks_blue_jump_kick_extension,
	ss_main_attacks_blue_jump_kick_hit,
	ss_main_attacks_blue_jump_kick_miss,
	ss_main_attacks_blue_whip_extension,
	ss_main_attacks_blue_whip_hit,
	ss_main_attacks_blue_whip_miss,
	ss_main_attacks_red_grab_extension,
	ss_main_attacks_red_grab_hit,
	ss_main_attacks_red_grab_miss,
	ss_main_attacks_red_jump_kick_extension,
	ss_main_attacks_red_jump_kick_hit,
	ss_main_attacks_red_jump_kick_miss,
	ss_main_attacks_red_whip_extension,
	ss_main_attacks_red_whip_hit,
	ss_main_attacks_red_whip_miss,
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
	ss_main_prompt_stop
};

enum MENU_SPRITESHEET
{
	ss_menu_cursor,
	ss_menu_how_to_play,
	ss_menu_title_screen
};

enum MUSIC_ORDER
{
	music_drum_beat,
	music_title_theme,
	music_yamborghini_high
};

enum SOUND_ORDER
{
	sound_combat_start,
	sound_cymbal_swell,
	sound_hit_1,
	sound_hit_2,
	sound_hit_3,
	sound_miss,
	sound_swell_to_hit,
	sound_round_end
};

enum CONTROLLER_DATA
{
	controller_options_nav,
	controller_combat_debug,
	controller_no_input,
	controller_combat_select_attack,
	controller_combat_fight,
	controller_rotation_point
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
	input_controller_player_2
};

enum DATA
{
	data_atlas,
	data_character,
	data_controller,
	data_options,
	data_audio,
};