#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	/*********************************** 0. Vertex Array ***********************/
	/*	Vertex Array stores: 
		- refrence to a vertex buffer
		- the attributes layout of that vertet buffer
		- reference to a index buffer

		For draw, all we need is to bind this vertex array alone.
		To setup a vertex array, after binding the vertex buffer:
		1. Bind vertex buffer to GL_ARRAY_BUFFER
		2. Set attrib layout and enable them
		3. Bind index buffer to GL_ELEMENT_ARRAY_BUFFER
		4. *DO NOT* unbind GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER before unbinding vertex array, otherwise references will be deleted.
	*/
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	/*********************************** 1. Vertex Buffer ***********************/
	float vertices[]{
		// We have one attribute ( 2 floats) per vertex ( 4 vertices)
		-0.5f, -0.5f, 
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	// 1. Create a (vertex/data) buffer
	unsigned int vb;
	glGenBuffers(1, &vb);

	// 2. Bind buffer to GL_ARRAY_BUFFER ==> for vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	// 3. (while binded) Set the data (for the buffer binded currently to GL_ARRAY_BUFFER)
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	// 4. (while binded) Set vertex attributes layout (for the buffer binded currently to GL_ARRAY_BUFFER)
	// set layout of attrib#0
	glVertexAttribPointer(	0, 
							2 , GL_FLOAT,		/*2 floats*/
							GL_FALSE,
							2 * sizeof(float),	/*size of each vertex*/
							0);					/*offset of this attrib in vertex*/
	// enable attrib #0
	glEnableVertexAttribArray(0);


	/*********************************** 2. Index Buffer ***********************/
	unsigned int indices[]{
		0,1,2,
		2,3,0
	};
	// 1. Create a (index) buffer
	unsigned int ib;
	glGenBuffers(1, &ib);
	// 2. Bind buffer to GL_ELEMENT_ARRAY_BUFFER ==> for vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	// 3. Set the data (for the buffer binded currently to GL_ELEMENT_ARRAY_BUFFER)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		UnbindAll();
		/* For Drawing:
			Since we already setup "Vertex Array" for our rectangular, we simply bind it and draw it.
			It automatically handle binding vertex buffer and index buffer and loading attrib layout.
		*/
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}