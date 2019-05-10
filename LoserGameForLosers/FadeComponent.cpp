#include "stdafx.h"

FadeComponent::FadeComponent(const int frames_per_cycle)
	: frames_per_cycle_(frames_per_cycle), cycles_completed_(0), texture_(nullptr), alpha_(255), waxing_(true)
{}

void FadeComponent::init()
{
	texture_ = &entity->get_component<TextureComponent>();
}

void FadeComponent::update()
{
	if (SDL_GetTicks() % frames_per_cycle_ == 0)
	{
		if (waxing_)
		{
			texture_->set_alpha(alpha_--);

			if (alpha_ == 0)
				waxing_ = false;
		}
		else
		{
			texture_->set_alpha(alpha_++);

			if (alpha_ == 0)
				waxing_ = true;

			cycles_completed_++;
		}
	}
}
