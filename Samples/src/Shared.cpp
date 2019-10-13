#include <GL/glew.h>
#include <iostream>

unsigned int CompileShader(unsigned int type, const std::string source)
{
	// 1. Create a shader
	unsigned int shaderId = glCreateShader(type);

	// 2. Specify the source of a shader
	const char* src = source.c_str(); // &source[0]
	glShaderSource(shaderId, 1, &src, nullptr);

	// 3. Compile Shader
	glCompileShader(shaderId);

	// 4. Check Error
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // allocate on stack dynamically
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cout << "Failed to compile "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader !" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderId);
	}

	return shaderId;
}


void UnbindEeverything() {
	/**
	 * Note: although we technically unbind, but it's not effective.
	 * e.g., if you want to understand if binding IBO is needed for each draw,
	 *		 don't rely on unbinding and checking if still works without rebinding.
	 *		 instead, bind some other IBO.
	 */

	 /*	Keep glBindVertexArray(0) before glBindBuffer(..,0). Why?
		 Unind VBO **BEFORE** unbinding VAO, delete VBO references from VAO.
	 */
	glBindVertexArray(0);						// unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// unbind IBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// unbind VBO
	glUseProgram(0);							// unbind Shader
}