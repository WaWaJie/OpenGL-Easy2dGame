#pragma once

#include"../glframework/core.h"
#include"../glframework/texture.h"
#include"../glframework/shader.h"

#include<vector>
#include"vector2.h"
#include"timer.h"
using TextureList = std::vector<Texture*>;


class Player
{
public:
	Player();
	~Player() = default;

	void on_update(float delta);
	void on_render(Shader* shader);

	void key_up(bool flag) { is_up_key_down = flag; }
	void key_down(bool flag) { is_down_key_down = flag; }

	const Vector2 get_position_ndc() const { return position_ndc; }
	const Vector2 get_size()const { return size_ndc; }

private:
	void on_key(int key, int action, int mods);
	

private:
	GLuint m_vao, m_ebo;
	TextureList texture_list;
	int m_unit = 1;
	Vector2 position_ndc = { -1.0,0.0 };
	Vector2 size_ndc = { 71.0 / 640,71.0 / 360 };
	bool is_up_key_down = false;
	bool is_down_key_down = false;
	float velocity_y = 1.0;

	Timer timer_animation;
	int idx = 0;
};