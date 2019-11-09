#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::load_texture(const std::string filename)
{
	auto tex = new Texture();

	if (tex->load_from_file(filename))
		textures_.push_back(tex);
}

void TextureManager::load_font(const std::string filename)
{
	auto tex = new Texture();

	if (tex->load_editable_texture_from_file(filename))
	{
		textures_.push_back(tex);

		auto font = new BitmapFont();

		if (font->build_font(tex))
			fonts_.push_back(font);
	}
}

void TextureManager::free_textures()
{
	for (auto& t : textures_)
		t->free();
}

Texture* TextureManager::get_texture(const int texture)
{
	return textures_[texture];
}

BitmapFont * TextureManager::get_font(const int font)
{
	return fonts_[font];
}
 