#if 0
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	

	/* To memorize
		Vertex Buffer Object	(VBO)	.........	Data/Vertices	...........	target: GL_ARRAY_BUFFER			.......	draw: glDrawArrays
		Index Buffer Object		(IBO)	.........	Ref to Vertices	...........	target: GL_ELEMENT_ARRAY_BUFFER	.......	draw: glDrawElements
	*/



	/*********************************** 0. Vertex Array ***********************/
	/*	Vertex Array stores: 
		- reference to a vertex buffer
		- the attributes layout of that vertex buffer
		- reference to a index buffer
		Therefore, For draw, all we need is to bind this vertex array alone.

		To setup VAO
		0. Create & bind VAO
		1. Create & Bind VBO to GL_ARRAY_BUFFER + Set attrib layout and enable them
		2. Create & bind IBO to GL_ELEMENT_ARRAY_BUFFER
		3. Unind VAO **BEFORE** unbinding VBO or IBO, otherwise references will be deleted.
	*/
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	/*********************************** 1. Vertex Buffer ***********************/
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


	/*********************************** 2. Index Buffer ***********************/
	unsigned int indices[]{
		0,1,2,
		2,3,0
	};
	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		/* For Drawing:
			Since we already setup VAO for our rectangular, we simply bind it and draw it.
			It automatically handle binding VBO, IBO and loading attrib layout.
		*/
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		UnbindEeverything();
		

		glfwSwapBuffers(window);
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}

void UnbindEeverything(){
	glBindVertexArray(0);						// unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// unbind IBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// unbind VBO
	glUseProgram(0);							// unbind Shader
}

#endif