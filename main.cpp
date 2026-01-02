/*
*	博主： WaWaJie
*	https://blog.csdn.net/2301_79921853?type=blog
* 
*/

#define STB_IMAGE_IMPLEMENTATION
#include"glframework/core.h"
#include"glframework/shader.h"
#include"application/stb_image.h"
#include"application/Application.h"
#include"glframework/texture.h"
#include"character/player.h"
#include"character/pea.h"
#include"character/enemy.h"

#include<vector>
#include<random>
#include<chrono>
#include<algorithm>

//纹理单元分配：
/*
0：背景地图
1：玩家动画
2: 子弹动画
3: 敌人动画
*/

using TextureList=std::vector<Texture*>;



void on_resize(int width, int height)
{
	glViewport(0, 0, width, height);
}




int idx = 1;
Shader* shader_normal;
Shader* shader_texture;
GLuint vao,vao2;
Texture* texture_bg;
Texture* texture_player;
Player* player;
std::vector<Pea*> pea_list;
std::vector<Enemy*> enemy_list;
Timer timer_generate_enemy;
Timer timer_can_shoot;

void prepare_shader()
{
    shader_normal = new Shader("assets/shader/vertex.glsl", "assets/shader/fragment.glsl");
	shader_texture = new Shader("assets/shader/vertex_texture.glsl", "assets/shader/fragment_texture.glsl");
}

void on_init()
{
	//设置随机数种子
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator1(seed1);
	std::uniform_int_distribution<int> dist1(1, 100);
	srand(seed1); 
	
	texture_bg = new Texture("assets/textures/background.png",0);
	player = new Player();
	
	Pea* pea = new Pea(player->get_position_ndc());
	app->set_keyboard_callback([](int key, int action, int mod)
		{
			switch (action)
			{
			case GLFW_PRESS:
				if (key == GLFW_KEY_W)
					player->key_up(true);
				if (key == GLFW_KEY_S)
					player->key_down(true);
				break;
			case GLFW_RELEASE:
				if (key == GLFW_KEY_W)
                    player->key_up(false);
				if (key == GLFW_KEY_S)
                    player->key_down(false);
				break;
			default:
				break;
			}
		});

	timer_can_shoot.set_one_shot(false);
	timer_can_shoot.set_wait_time(0.5);
	timer_can_shoot.set_on_timeout([&]()
		{
			pea_list.push_back(new Pea(player->get_position_ndc()));
		});

	timer_generate_enemy.set_one_shot(false);
	timer_generate_enemy.set_wait_time(2.0);
	timer_generate_enemy.set_on_timeout([&]()
		{
			float x = 1.0;
			float y = float(rand() % 720) / 360.0 - 1.0;
			if (y < -1.0 + 200.0 / 720.0)y = -1.0 + 200.0 / 720.0;
			enemy_list.push_back(new Enemy(Vector2(x, y)));
		});
}

void prepare_vao()
{
	float positions[] = {
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		-1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
	};

	float uvs[] = {
		0.0f,0.0f,
		2.0f,0.0f,
		0.0f,2.0f,
		2.0f,2.0f,
	};

	float positions2[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
	};

	float uvs2[] = {
		0.0f,0.0f,
		1.0f,0.0f,
		0.0f,1.0f,
		1.0f,1.0f,
	};

	unsigned int indices[] = {
		0,1,2,
		2,1,3,
	};

	GLuint vbo_pos, vbo_uv;
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    
	glGenBuffers(1, &vbo_uv);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
	//vao绑定
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);	
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(0);


	GLuint vbo_pos2, vbo_uv2;
	glGenBuffers(1, &vbo_pos2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions2), positions2, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo_uv2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs2), uvs2, GL_STATIC_DRAW);
	//vao绑定
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos2);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv2);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(0);
}

void on_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	shader_texture->on_begin();/**/
	
	shader_texture->set_uniform_1i("sampler", 0);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);

    for (auto& enemy : enemy_list)
        enemy->on_render(shader_texture);
	for (auto& pea : pea_list)
		pea->on_render(shader_texture);
	player->on_render(shader_texture);

	shader_texture->on_end();/**/
}

int main()
{

	if (!app->on_init(1280, 720))
		return -1;
	app->set_window_resize_callback(on_resize);
	glViewport(0, 0, 1280, 720);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	prepare_shader();
	prepare_vao();
	on_init();
	
	int count = 0;

	static float last_tick = glfwGetTime();

	while (app->on_update())
	{
		float current_tick= glfwGetTime();
		float delta = current_tick - last_tick;
		last_tick=current_tick;
		timer_can_shoot.on_update(delta);
		timer_generate_enemy.on_update(delta);
		
		
        
		for (auto& pea : pea_list)
		{
			if (!pea->can_collide())
				break;
			for (auto& enemy : enemy_list)
			{
                enemy->check_collision_to_bullet(*pea);
			}
		}
		for (auto& enemy : enemy_list)
		{
			enemy->on_update(delta);
			enemy_list.erase(remove_if(enemy_list.begin(), enemy_list.end(),
				[](Enemy* enemy) {
					if (enemy->can_remove())
					{
						delete enemy;
						return true;
					}
					return false;
				}),
				enemy_list.end());
		}
		for (auto& pea : pea_list)
		{
			pea->on_update(delta);
			pea_list.erase(remove_if(pea_list.begin(), pea_list.end(),
				[](Pea* pea) {
					if (pea->can_remove())
					{
						delete pea;
						return true;
					}
					return false;
				}),
				pea_list.end());
		}

		player->on_update(delta);
		on_render();
	}
	app->on_destroy();


	return 0;
}