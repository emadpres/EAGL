#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "Renderer.h"


namespace eagl {

	Shader::Shader(std::string filepath)
	{
		const auto shadersSrc = ReadFile(filepath);

		m_rendererId = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, shadersSrc.first);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shadersSrc.second);
		glAttachShader(m_rendererId, vs);
		glAttachShader(m_rendererId, fs);
		glLinkProgram(m_rendererId);
		glValidateProgram(m_rendererId);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_rendererId);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_rendererId);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	unsigned int Shader::CompileShader(unsigned int type, std::string source)
	{
		unsigned int id = glCreateShader(type);
		const char *src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char)); // allocate on stack dynamically 
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile "
				<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				<< " shader !" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
		}

		return id;
	}

	std::pair<std::string, std::string> Shader::ReadFile(std::string filepath)
	{
		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		} currentType = ShaderType::NONE;
		std::stringstream shaders[2];
		std::ifstream input(filepath);
		ASSERT(input.is_open());

		std::string line;
		while (!input.eof())
		{
			std::getline(input, line);
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					currentType = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					currentType = ShaderType::FRAGMENT;
				else
					ASSERT(0);
			}
			else
			{
				shaders[static_cast<int>(currentType)] << line << std::endl;
			}
		}

		//std::cout << "Vertex " << std::endl << shaders[0].str() << std::endl;
		//std::cout << "Fragment " << std::endl << shaders[1].str() << std::endl;

		return std::make_pair(shaders[0].str(), shaders[1].str());
	}

	void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
	{

		int location = glGetUniformLocation(m_rendererId, name);
		ASSERT(location != -1);
		// TODO: cache this location
		glUniform4f(location, v0, v1, v2, v3);
	}

}
