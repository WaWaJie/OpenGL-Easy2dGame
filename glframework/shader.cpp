#include"shader.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

Shader::Shader(const char* vertex_path, const char* fragment_path)
{ 
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;
	vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertex_shader_file.open(vertex_path);
		fragment_shader_file.open(fragment_path);

		std::stringstream vertex_shader_str, fragment_shader_str;
		vertex_shader_str << vertex_shader_file.rdbuf();
		fragment_shader_str << fragment_shader_file.rdbuf();

		vertex_shader_file.close();
		fragment_shader_file.close();

		vertex_code = vertex_shader_str.str();
		fragment_code = fragment_shader_str.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR: Shader File Error" << e.what() << std::endl;
	}

	const char* vertex_shader_source = vertex_code.c_str();
	const char* fragment_shader_source = fragment_code.c_str();

	//2.创建Shader程序
	GLuint vertex_shader, fragment_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	//3.为Shader程序输入Shader代码
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

	int success = 0;
	char infoLog[1024];
	//4.执行Shader代码编译
	glCompileShader(vertex_shader);
	//检查vertex_shader编译结果
	check_shader_error(vertex_shader, "COMPILE");
	//检查fragment_shader编译结果
	glCompileShader(fragment_shader);
	check_shader_error(fragment_shader, "COMPILE");
	//5.创建一个Program壳子
	m_program = glCreateProgram();

	//6.将vs与fs编译好的结果放到program这个壳子里
	glAttachShader(m_program, vertex_shader);
	glAttachShader(m_program, fragment_shader);

	//7.执行program 的链接操作，形成最终可执行的shader程序
	glLinkProgram(m_program);
	check_shader_error(m_program, "LINK");

	//清理
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}
Shader::~Shader()
{
    glDeleteProgram(m_program);
}
void Shader::check_shader_error(GLuint shader, const std::string& type)
{ 
    int success;
    char info_log[512];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << info_log << std::endl;
        }
    }

    else
    {
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, info_log);
            std::cout << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << info_log << std::endl;
        }
    }
    return;
}

void Shader::on_begin() const
{
    glUseProgram(m_program);
}
void Shader::on_end() const
{
    glUseProgram(0);
}

void Shader::set_uniform_1f(const std::string& name, float value) const
{
	GLuint location = glGetUniformLocation(m_program, name.c_str());
	glUniform1f(location, value);
}
void Shader::set_uniform_1i(const std::string& name, int value) const
{
	GLuint location = glGetUniformLocation(m_program, name.c_str());
	glUniform1i(location, value);
}

