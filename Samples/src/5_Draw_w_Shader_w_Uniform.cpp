#if 0

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
	glfwSwapInterval(1);
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


	/** 3. Shader ******/
	unsigned int programId = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,	"#version 330 core\n"
														"layout(location = 0) in vec4 position;\n"	
														"void main() {\n"
														"	gl_Position = position;\n"
														"}");

	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, "#version 330 core\n"
														"layout(location = 0) out vec4 color;\n"
														"uniform vec4 u_Color;" // NEW
														"void main() {\n"
														"	color = u_Color;\n" // NEW
														"}");
	glAttachShader(programId, vs);
	glAttachShader(programId, fs);
	glLinkProgram(programId);
	glValidateProgram(programId);
	glDeleteShader(vs);
	glDeleteShader(fs);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);


		glBindVertexArray(vao);
		/*********************************** Uniform ***********************/
		// 1. After binding shader
		glUseProgram(programId);
		// 2. Get uniform variable location (we use program, not specific shader)
		int loc = glGetUniformLocation(programId, "u_Color");
		// 3. Set uniform value
		glUniform4f(loc, rand()/float(RAND_MAX), 0.4f, 0.1f, 1.f);
		/*------------------------------------------------------------------*/
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		UnbindEeverything();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#endif