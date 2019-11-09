#pragma once
#include "SDL.h"
#include <string>
#include "Texture.h" 

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

class BitmapFont
{
public:
	//The default constructor
	BitmapFont();

	//Generates the font
	bool build_font(Texture * tex);

	//Shows the text
	void render_text(const int x, const int y, std::string text);

	SDL_Rect* text_dimensions(int x, int y, std::string text);

private:
	//The font texture
	Texture *map_bitmap_;

	void* map_pixels_;

	//The individual characters in the surface
	SDL_Rect map_chars_[256]{};

	//Spacing Variables
	int map_new_line_, map_space_;
};