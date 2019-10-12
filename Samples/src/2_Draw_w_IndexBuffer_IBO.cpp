#if 0
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void UnbindEverything();

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
	glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
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


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		
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
		// glDrawElements uses "count" sequential elements from currently binded GL_ARRAY_BUFFER, starting at "indices" to construct a sequence of "geometric primitives".
		glDrawElements(	GL_TRIANGLES,		/*what geometric primitive, e.g., GL_TRIANGLE*/
						6,					/*count = number of vertices*/ /* here it draw every 3 (<--because of GL_TRIANGLES) vertices (in total 6 vertices) according to IBO's references to VBO*/
						GL_UNSIGNED_INT,	/*type of index data*/
						NULL);				/*pointer to indices or NULL*/
		UnbindEverything();
		

		glfwSwapBuffers(window);
		glfwPollEvents();		
	}
	glfwTerminate();
	return 0;
}

void UnbindEverything()
{
	glBindVertexArray(0);						// unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// unbind IBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// unbind VBO
	glUseProgram(0);							// unbind Shader
}

#endif