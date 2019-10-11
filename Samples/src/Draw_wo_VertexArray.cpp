#if 0
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

void UnbindAll()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

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
	
	/*********************************** 1. Vertex Buffer ***********************/
	float vertices[]{
		// We have one attribute ( 2 floats) per vertex ( 4 vertices)
		-0.5f, -0.5f, 
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	// 1. Create a (vertex or data) buffer
	unsigned int vb;
	glGenBuffers(1, &vb);

	// 2. Bind buffer to GL_ARRAY_BUFFER ==> for vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	// 3. (while binded) Set vertex buffer data (for the buffer binded currently to GL_ARRAY_BUFFER)
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	// 4. (while binded) Set vertex buffer layout (for the buffer binded currently to GL_ARRAY_BUFFER)
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
	
	// 2. Bind buffer to GL_ELEMENT_ARRAY_BUFFER ==> for index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	
	// 3. (while binded) Set the data (for the buffer binded currently to GL_ELEMENT_ARRAY_BUFFER)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		UnbindAll();
		/* For Drawing:
			Since by default we are in OpenGL_Compatibility_profile, a *single* "Vertex Array" is created for us.
			which is shared for all drawing. To setup this vertex array, for every draw, we need to:
			- Bind vertex buffer
			- (while binded) Set the attributes layout, and enable attributes
			- (optionally) (while binded) Bind index buffer
		*/
		glBindBuffer(GL_ARRAY_BUFFER, vb);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,2 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}

#endif