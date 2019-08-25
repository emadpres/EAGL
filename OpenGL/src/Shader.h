#pragma once

#include <string>
#include <utility>

namespace eagl {
	class Shader
	{
		unsigned int m_rendererId;

	private:
		std::pair<std::string, std::string> ReadFile(std::string filepath);
		unsigned int CompileShader(unsigned int type, std::string source);
	public:
		Shader(std::string filepath);
		~Shader();

		void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);

		void Bind() const;
		void UnBind() const;

	};
}