#include "stdafx.h"

FadeComponent::FadeComponent(const Uint8 frames_per_cycle)
	: frames_per_cycle_(frames_per_cycle), cycles_completed_(0), texture_(nullptr), alpha_(255), waxing_(true)
{}

void FadeComponent::init()
{
	texture_ = &entity->get_component<TextureComponent>();
}

void FadeComponent::update()
{
	if (waxing_)
	{
		texture_->set_alpha(alpha_);

		alpha_ -= frames_per_cycle_;

		if (alpha_ == 0)
		{
			waxing_ = false;
			cycles_completed_++;
		}
	}
	else
	{
		texture_->set_alpha(alpha_++);

		alpha_ += frames_per_cycle_;

		if (alpha_ >= 255)
		{
			waxing_ = true;
		}
	}
}
