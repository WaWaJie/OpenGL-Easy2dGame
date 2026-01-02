#pragma once

#include"../glframework/core.h"
#include"../glframework/texture.h"
#include"../glframework/shader.h"
#include"pea.h"

#include<vector>
#include"vector2.h"
#include"timer.h"

class Enemy
{
public:
	Enemy(const Vector2& pos);
	~Enemy();

	void on_update(float delta);

	void on_render(Shader* shader);

	bool can_remove()const { return !is_valid; }

	void check_collision_to_bullet(Pea& bullet);

private:
	GLuint m_vao, m_ebo;
	int m_unit = 3;
	Vector2 position_ndc = { -1.0,0.0 };
	Vector2 size_ndc = { 80.0 / 640,80.0 / 360 };

	float velocity_x = 0.2;
	bool can_collide = true;
	bool is_valid = true;
	bool is_invulnerable = false;
	bool is_blinking = false;

	Timer timer_animation;
	Timer timer_invulnerable;
	Timer timer_blink;
	int idx = 0;
	int hp = 3;
};
