#include"Application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<functional>

Application* Application::instance = nullptr;

Application* Application::get_instance()
{
	if(!instance)
        instance = new Application();
    return instance;
}
bool Application::on_init(const int& width, const int& height)
{ 
    //初始化GLFW的基本环境
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (m_window == NULL) { return false; }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
    glfwSetKeyCallback(m_window, key_callback);
    // 开启混合功能
    glEnable(GL_BLEND);
    // 设置混合因子：
    // 最终颜色 = (源颜色 * 源因子) + (目标颜色 * 目标因子)
    // 这里使用常见的Alpha混合公式：
    // 源因子为当前像素的Alpha值，目标因子为1 - 源Alpha值
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    load_bullet_texture();
    load_enemy_texture();
    return true;
}

void Application::frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Resize" << std::endl;
    Application* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->m_frame_resize_callback != nullptr)
    {
        self->m_frame_resize_callback(width, height);
    }
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->m_keyboard_callback != nullptr)
    {
        self->m_keyboard_callback(key, action, mods);
    }
}

bool Application::on_update()
{
    if (glfwWindowShouldClose(m_window))return false;
    glfwPollEvents();
    glfwSwapBuffers(m_window);

    return true;
}

void Application::on_destroy()
{
    glfwTerminate();
}


Application::Application()
{

}
Application::~Application()
{

}

void Application::load_bullet_texture()
{ 
    texture_list_bullet.push_back(new Texture("assets/textures/PeaBullet/PeaBullet0.png", 2));
    texture_list_bullet.push_back(new Texture("assets/textures/PeaBullet/PeaBullet1.png", 2));
    texture_list_bullet.push_back(new Texture("assets/textures/PeaBullet/PeaBullet2.png", 2));
    texture_list_bullet.push_back(new Texture("assets/textures/PeaBullet/PeaBullet3.png", 2));
    texture_list_bullet.push_back(new Texture("assets/textures/PeaBullet/PeaNormalExplode_0.png", 2));
}

void Application::load_enemy_texture()
{
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_0.png", 3));
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_1.png", 3));
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_2.png", 3));
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_3.png", 3));
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_4.png", 3));
    texture_list_enemy.push_back(new Texture("assets/textures/enemy/enemy_left_5.png", 3));
}