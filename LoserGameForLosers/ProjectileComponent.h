#pragma once

struct Projectile
{
	std::vector<int> slots;
	Vector2D position_offset;
	Vector2D direction;
};

class ProjectileComponent : public Component
{
	Entity * player_;
	TextureAtlasComponent* texture_;
	TransformComponent * player_transform_;
	std::vector<Projectile> projectiles_;
	int attack_distance_;
	int projectile_size_;
public:
	ProjectileComponent(Entity * player);
	void init() override;
	void update() override;

};