#pragma once

//加载纹理并绑定对应的纹理单元

#include"core.h"
#include<string>

class Texture
{
public:
	Texture(const std::string& path, unsigned int unit);
	~Texture();


	void bind();
	int get_width()const{return m_width;}
	int get_height()const{return m_height;}

private:
	GLuint m_texture{ 0 };
    int m_width{ 0 };
    int m_height{ 0 };
    unsigned int m_unit{ 0 };

};