#pragma once

class FadeComponent : public Component
{
	Uint8 frames_per_cycle_;
	int cycles_completed_;
	TextureComponent * texture_;
	Uint8 alpha_;
	bool waxing_;
public:
	explicit FadeComponent(Uint8 frames_per_cycle);

	void init() override;
	void update() override;
	int cycles_completed() const { return cycles_completed_; }
};