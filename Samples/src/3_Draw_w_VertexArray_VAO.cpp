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



	/*********************************** 0.  Vertex Array (NEW) ***********************/
	/*	To avoid setting VBO layout after every VBO(GL_ARRAY_BUFFER) binding, we can use "Vertex Array Object" which stores:
		- reference to a VBO
		- the VBO's attributes layout

		To setup VAO:
		0. Create & bind VAO
		1. Create & Bind VBO to GL_ARRAY_BUFFER
		2. Set attrib layout and enable them
		3. Unind VAO **BEFORE** unbinding VBO, otherwise references will be deleted.
	*/
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


	/** 2. Index Buffer ****/
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
			BEFORE USING VAO:
				By default we are in OpenGL_Compatibility_profile, and a *shared* "Vertex Array" is created for us.
				So when for every draw, we bind VBO and set its layout, it applies on the shared VAO behind the scene.
			AFTER USING VAO:
			Now, since we already setup VAO for our rectangular, we only need to bind (in arbitrary order):
			- VAO (it take cares of binding VBO and setting its layout)
			- IBO
			- Shader
			- DRAW !!!
		*/
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
		//glUseProgram(...) //when we have shader
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		UnbindEeverything();

		glfwSwapBuffers(window);
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}

#endif