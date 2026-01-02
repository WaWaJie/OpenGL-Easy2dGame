
#include"enemy.h"
#include"../application/Application.h"


Enemy::Enemy(const Vector2& pos)
{
	position_ndc.x = pos.x;
	position_ndc.y = pos.y;

	timer_animation.set_wait_time(0.1f);
	timer_animation.set_one_shot(false);
	timer_animation.set_on_timeout([&]()
		{
			idx = (idx + 1) % (app->texture_list_enemy.size());
			app->texture_list_enemy[idx]->bind();
		});

	timer_blink.set_wait_time(0.1f);
	timer_blink.set_one_shot(false);
	timer_blink.set_on_timeout([&]()
		{
			is_blinking= !is_blinking;
		});

	timer_invulnerable.set_wait_time(0.15f);
	timer_invulnerable.set_one_shot(true);
	timer_invulnerable.set_on_timeout([&]()
		{
			is_invulnerable = false;
			is_blinking = false;
		});


	glGenVertexArrays(1, &m_vao);

	static unsigned int indices[] = {
		0,1,2,
		2,1,3,
	};
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Enemy::~Enemy()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);
}

void Enemy::on_update(float delta)
{
	timer_animation.on_update(delta);
	if(is_invulnerable)
		timer_blink.on_update(delta);
	timer_invulnerable.on_update(delta);
	float scale = 1.5;

	position_ndc.x = (position_ndc.x - delta * velocity_x);
	if (position_ndc.x < -1.0f)can_collide = false, is_valid = false;

	float positions[] = {
		position_ndc.x,position_ndc.y - size_ndc.y * scale,0.0f,
		position_ndc.x + size_ndc.x * scale,position_ndc.y - size_ndc.y * scale,0.0f,
		position_ndc.x,position_ndc.y,0.0f,
		position_ndc.x + size_ndc.x * scale,position_ndc.y,0.0f,
	};

	static float uvs[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		1.0f,1.0f,
	};


	GLuint vbo_pos, vbo_uv;
	glGenBuffers(1, &vbo_pos);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glGenBuffers(1, &vbo_uv);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glBindVertexArray(m_vao);
	//vao绑定
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBindVertexArray(0);

	glDeleteBuffers(1, &vbo_pos);
	glDeleteBuffers(1, &vbo_uv);
}

void Enemy::on_render(Shader* shader)
{
	app->texture_list_enemy[idx]->bind();
	shader->on_begin();
	shader->set_uniform_1i("sampler", m_unit);
	if (is_blinking)
		shader->set_uniform_1i("invulnerable", 1);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	shader->set_uniform_1i("invulnerable", 0);
	shader->on_end();
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Enemy::check_collision_to_bullet(Pea&bullet)
{
	const Vector2& pos = bullet.get_position_ndc();
	if (pos.x >= position_ndc.x && pos.x <= (position_ndc.x + size_ndc.x)
		&& pos.y >= (position_ndc.y - size_ndc.y) && pos.y <= position_ndc.y)
	{
		bullet.on_collide();
		hp--;
		is_invulnerable = true;
		is_blinking = true;
		timer_blink.restart();
		timer_invulnerable.restart();
		if (hp <= 0)
		{
			is_valid = false;
		}
	}
}