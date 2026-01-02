#include"player.h"
#include<iostream>
#include"../application/Application.h"

Player::Player()
{
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_0.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_1.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_2.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_3.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_4.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_5.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_6.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_7.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_8.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_9.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_10.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_11.png", m_unit));
	texture_list.push_back(new Texture("assets/textures/PeaShooter/Peashooter_12.png", m_unit));

	timer_animation.set_wait_time(0.07f);
	timer_animation.set_one_shot(false);
	timer_animation.set_on_timeout([&]()
		{
			idx = (idx + 1) % 13;
			texture_list[idx]->bind();
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

void Player::on_update(float delta)
{
	
	timer_animation.on_update(delta);
	float scale = 1.0;
	
	int move_dir = is_up_key_down - is_down_key_down;
	position_ndc.y = (position_ndc.y + move_dir * delta * velocity_y);
	if (position_ndc.y - size_ndc.y < -1.0f)
		position_ndc.y = -1.0f + size_ndc.y;
    if(position_ndc.y > 1.0f)
		position_ndc.y = 1.0f;

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

void Player::on_render(Shader*shader)
{
	shader->on_begin();
	shader->set_uniform_1i("sampler", m_unit);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	shader->on_end();
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

