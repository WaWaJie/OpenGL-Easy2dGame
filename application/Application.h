#pragma once

#include<iostream>
#include<vector>
#include"../glframework/texture.h"

using WindowResizeCallback = void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);

class GLFWwindow;
#define app Application::get_instance()

using TextureList = std::vector<Texture*>;

class Application
{

public:
	static Application* get_instance();

	bool on_init(const int& width, const int& height);
	bool on_update();
	void on_destroy();

	void set_window_resize_callback(WindowResizeCallback callback){m_frame_resize_callback = callback;}
	void set_keyboard_callback(KeyBoardCallback callback){m_keyboard_callback = callback;}

	uint32_t get_window_width() const;
    uint32_t get_window_height() const;

private:
	static void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void load_bullet_texture();
    void load_enemy_texture();

private:
	Application();
	~Application();
	static Application* instance;

	uint32_t m_window_width;
	uint32_t m_window_height;
    WindowResizeCallback m_frame_resize_callback;
    KeyBoardCallback m_keyboard_callback;
	GLFWwindow* m_window{ nullptr };

public:
	TextureList texture_list_bullet;
	TextureList texture_list_enemy;
};