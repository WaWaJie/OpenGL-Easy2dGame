#pragma once

#include"../glframework/core.h"
#include"../glframework/texture.h"
#include"../glframework/shader.h"
#include"../application/Application.h"

#include<vector>
#include"vector2.h"
#include"timer.h"

using TextureList = std::vector<Texture*>;

class Pea
{
public:
	Pea(const Vector2& pos);
	~Pea();

	void on_update(float delta);

	void on_render(Shader* shader);
	bool can_remove() { return !is_valid; }

	void on_collide() { isnt_collide = false; idx = app->texture_list_bullet.size() - 1; }
	bool can_collide() { return isnt_collide; }
	const Vector2 get_position_ndc() const { return position_ndc; }
	const Vector2 get_size()const { return size_ndc; }

private:
	GLuint m_vao, m_ebo;
	int m_unit = 2;
	Vector2 position_ndc = { -1.0,0.0 };
	Vector2 size_ndc = { 24.0 / 640,24.0 / 360 };

	float velocity_x = 1.0;
	bool isnt_collide = true;
	bool is_valid = true;

	Timer timer_animation;
	Timer timer_collide_callback;
	int idx = 0;

};