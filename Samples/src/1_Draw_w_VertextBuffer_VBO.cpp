#if 0

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //default mode

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
	*/


	/*********************************** 1. Vertex Buffer (NEW)***********************/
	float vertices[]{
		// We have vertex (4 vertices), each composed of one attribute (=position =2 floats)
		-0.5f, -0.5f, 
		 0.5f, -0.5f,
		 0.5f,  0.5f,
	};

	// 1. Create a (vertex/data) buffer
	unsigned int vb;
	glGenBuffers(	1,		/*how many buffer*/
					&vb);	/*return value for the id of soon-be-created buffer*/

	// 2. Bind buffer to GL_ARRAY_BUFFER ==> for vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	// 3. (while binded) Set the data (for the buffer binded currently to GL_ARRAY_BUFFER)
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);

	// 4. (while binded) Set vertex attributes layout (for the buffer binded currently to GL_ARRAY_BUFFER)
	glVertexAttribPointer(	0,					/* Attribute at index 0*/
							2 , GL_FLOAT,		/*2 floats*/
							GL_FALSE,
							2 * sizeof(float),	/*size of each vertex*/
							0);					/*offset of this attrib in vertex*/
	// 5. Enable attrib at index 0
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		
		/* For Drawing:
			Since by default we are in OpenGL_Compatibility_profile, a *single* "Vertex Array" is created for us.
			which is shared for all drawing. To setup this vertex array, for every draw, we need to:
			- Bind vertex buffer
			- (while VBO binded) Set the attributes layout, and enable attributes
			- DRAW !!!!
			
		*/
		glBindBuffer(GL_ARRAY_BUFFER, vb);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		/*	DRAW:
			glDrawArrays uses "count" sequential elements from already binded GL_ARRAY_BUFFER to construct 
			a sequence of "geometric primitives", beginning with element "first".*/
		glDrawArrays(	GL_TRIANGLES,	/*what geometric primitive, e.g., GL_TRIANGLE*/
						0,				/*first = starting index in vertex buffer*/
						3);				/*count = number of vertices*/	/* here it draw every 3 (<--because of GL_TRIANGLES) vertices startinf from #0 until #2 (in total 3 verices)*/
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vertex array
		

		glfwSwapBuffers(window);
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}


#endif