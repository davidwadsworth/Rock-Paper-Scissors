#include "stdafx.h"
#include "Texture.h"
#include "SDL_Image.h"

Texture::Texture()
{
	//Initialize
	map_texture_ = nullptr;
	map_width_ = 0;
	map_height_ = 0;
	map_pixels_ = NULL;
	map_pitch_ = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::load_editable_texture_from_file(std::string path)
{	
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* new_texture = nullptr;

	//Load image at specified path
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());

	if (loaded_surface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formatted_surface = SDL_ConvertSurfaceFormat(loaded_surface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formatted_surface == nullptr)
		{
			printf("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			new_texture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formatted_surface->w, formatted_surface->h);
			if (new_texture == nullptr)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(new_texture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(new_texture, &formatted_surface->clip_rect, &map_pixels_, &map_pitch_);

				//Copy loaded/formatted surface pixels
				memcpy(map_pixels_, formatted_surface->pixels, static_cast<unsigned>(formatted_surface->pitch * formatted_surface->h));

				//Get image dimensions
				map_width_ = formatted_surface->w;
				map_height_ = formatted_surface->h;

				//Get pixel data in editable format
				Uint32* pixels = static_cast<Uint32*>(map_pixels_);
				const int pixelCount = (map_pitch_ / 4) * map_height_;

				//Map colors				
				const Uint32 colorKey = SDL_MapRGB(formatted_surface->format, 0, 0xFF, 0xFF);
				const Uint32 transparent = SDL_MapRGBA(formatted_surface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (auto i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(new_texture);
				map_pixels_ = nullptr;

			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formatted_surface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	//Return success
	map_texture_ = new_texture;
	return map_texture_;
}

bool Texture::load_from_file(std::string path)
{
	free();

	const auto temp_surface = IMG_Load(path.c_str());
	map_texture_ = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	return map_texture_;
}

void Texture::free()
{
	//Free texture if it exists
	if (map_texture_ != NULL)
	{
		SDL_DestroyTexture(map_texture_);
		map_texture_ = nullptr;
		map_width_ = 0;
		map_height_ = 0;
		map_pixels_ = nullptr;
		map_pitch_ = 0;
	}
}

void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(map_texture_, red, green, blue);
}

void Texture::set_blend_mode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(map_texture_, blending);
}

void Texture::set_alpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(map_texture_, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, map_width_, map_height_ };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(Game::renderer, map_texture_, clip, &renderQuad, angle, center, flip);
}

void Texture::render(SDL_Rect * src, SDL_Rect * dest, double rotation, SDL_Point * rotation_point, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, map_texture_, src, dest, rotation, rotation_point, flip);
}

int Texture::get_width()
{
	return map_width_;
}

int Texture::get_height()
{
	return map_height_;
}

bool Texture::lock_texture()
{
	bool success = true;

	//Texture is already locked
	if (map_pixels_ != NULL)
	{
		printf("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(map_texture_, nullptr, &map_pixels_, &map_pitch_) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool Texture::unlock_texture()
{
	bool success = true;

	//Texture is not locked
	if (map_pixels_ == nullptr)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(map_texture_);
		map_pixels_ = nullptr;
		map_pitch_ = 0;
	}

	return success;
}

void* Texture::get_pixels()
{
	return map_pixels_;
}

int Texture::get_pitch()
{
	return map_pitch_;
}

Uint32 Texture::get_pixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)map_pixels_;

	//Get the pixel requested
	return pixels[(y * (map_pitch_ / 4)) + x];
}

SDL_Texture* Texture::get_texture()
{
	return map_texture_;
}