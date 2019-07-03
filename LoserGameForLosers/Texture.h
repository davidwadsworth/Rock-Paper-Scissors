#pragma once
#include <string>
#include "SDL.h"

class DrawCall;

class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	bool load_editable_texture_from_file(std::string path);

	bool load_from_file(std::string path);


	//Deallocates texture
	void free();

	//Set color modulation
	void set_color(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void set_blend_mode(SDL_BlendMode blending);

	//Set alpha modulation
	void set_alpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(SDL_Rect* src, SDL_Rect* dest, double rotation, SDL_Point* rotation_point, SDL_RendererFlip flip);

	//Gets image dimensions
	int get_width();
	int get_height();

	//Pixel manipulators
	bool lock_texture();
	bool unlock_texture();
	void* get_pixels();
	int get_pitch();
	Uint32 get_pixel32(unsigned int x, unsigned int y);
	SDL_Texture * get_texture();

private:
	//The actual hardware texture
	SDL_Texture * map_texture_;
	void* map_pixels_;
	int map_pitch_;

	//Image dimensions
	int map_width_;
	int map_height_;
};
