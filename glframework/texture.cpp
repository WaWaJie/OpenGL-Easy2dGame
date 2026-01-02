#include"texture.h"
#include"../application/stb_image.h"
#include<iostream>

Texture::Texture(const std::string& path, unsigned int unit)
{
	//1.从硬盘中加载图片资源到内存当中(由CPU完成)
	int channel;
	m_unit = unit;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &channel, STBI_rgb_alpha);
	//2.创建纹理，激活纹理单元，绑定纹理对象
	glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	//3.传输纹理数据到GPU，开辟显存空间
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//4.设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//5.设置值纹理的包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);
}

Texture::~Texture()
{
	if (m_texture != 0) {
		glDeleteTextures(1, &m_texture);
	}
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}