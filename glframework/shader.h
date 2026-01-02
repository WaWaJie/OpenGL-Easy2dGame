#pragma once
//加载着色器

#include"core.h"
#include<string>

class Shader
{
public:
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    void on_begin() const;
    void on_end() const;

    void check_shader_error(GLuint shader, const std::string& type);
    void set_uniform_1i(const std::string& name, int value) const;
    void set_uniform_1f(const std::string& name, float value) const;

private:
    GLuint m_program;
};
