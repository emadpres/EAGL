#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int CompileShader(unsigned int type, const std::string source);
void UnbindEeverything();

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();
	std::cout << glGetString(GL_VERSION) << std::endl;
	

	/** 0. Vertex Array ******/
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	/** 1. Vertex Buffer ****/
	float vertices[]{
		-0.5f, -0.5f, 
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};
	unsigned int vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);


	/** 2. Index Buffer ******/
	unsigned int indices[]{
		0,1,2,
		2,3,0
	};
	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	/*********************************** 3. Shader (NEW)***********************/
	unsigned int programId = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,	"#version 330 core\n"						// GLSL (OpenGL Shader Language) v330 - core=no deprecated allowed
														"layout(location = 0) in vec4 position;\n"	// implicitly convert vec2(two float we specified) to vec4
														"void main() {\n"
														"	gl_Position = position;\n"				// gl_Position is vec4
														"}");

	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,	"#version 330 core\n"
														"layout(location = 0) out vec4 color;\n"
														"void main() {\n"
														"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"	//RGBA [0-1]
														"}");
	glAttachShader(programId, vs);
	glAttachShader(programId, fs);
	glLinkProgram(programId);
	glValidateProgram(programId);
	// Now that we have final linked shader (~.exe), we don't need intermediate files (~.obj)
	glDeleteShader(vs);
	glDeleteShader(fs);



	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		

		/* For Drawing (in arbitrary order):
			- VAO (it take cares of binding VBO and setting its layout)
			- IBO
			- Shader
			- DRAW !!!
		*/
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
		glUseProgram(programId);  // NEW -> bind shader
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		UnbindEeverything();
		

		glfwSwapBuffers(window);
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}
#endif