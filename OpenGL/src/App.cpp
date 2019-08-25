#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertextBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

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
	window = glfwCreateWindow(640, 480, "OpenGL World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Init Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	

	// 1. Triangle
	float vertices_triangle[]{
		-0.5f, -0.5f, 
		 0.5f, -0.5f,
		 0.5f,  0.5f,
	};
	eagl::VertexBuffer vb_triangle(6 * sizeof(float), vertices_triangle);
	eagl::BufferLayout layout;
	layout.Add(2, GL_FLOAT);
	eagl::VertexArray va_triangle(&vb_triangle, layout, nullptr);


	// 2. Rectangle
	float vertices_rectangle[]{
	-0.5f, -0.25f,
	 0.5f, -0.25f,
	 0.5f,  0.25f,
	-0.5f,  0.25f
	};
	eagl::VertexBuffer vb_rectangle(8 * sizeof(float), vertices_rectangle);

	unsigned int indices_rectangle[]{
		0,1,2,
		2,3,0
	};
	eagl::IndexBuffer ib_rectangle(6, GL_UNSIGNED_INT, indices_rectangle);

	eagl::BufferLayout layout_rectangle;
	layout_rectangle.Add(2, GL_FLOAT);
	eagl::VertexArray va_rectangle(&vb_rectangle, layout_rectangle, &ib_rectangle);


	eagl::Shader shader_red("res/shader/red.glsl");
	eagl::Shader shader_uniform("res/shader/uniformColor.glsl");

	float r = 0, r_inc = 0.05;
	float x_offset = 0, y_offset=0, xy_offset_inc = 0.05;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		eagl::UnbindAll();
		shader_uniform.Bind();
		shader_uniform.SetUniform4f("u_color", r, 0.6f, 0.6f, 1.f);
		shader_uniform.SetUniform4f("u_pos_offset", x_offset, y_offset, 0.0f, 0.0f);
		va_triangle.Bind();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		va_rectangle.Bind();
		shader_red.Bind();
		glDrawElements(GL_TRIANGLES, ib_rectangle.GetCount(), ib_rectangle.GetType(), nullptr);
		

		if (x_offset > 0.5 || x_offset < -0.5) xy_offset_inc *= -1;
		x_offset += xy_offset_inc;
		y_offset += xy_offset_inc;

		if (r < 0 || r>1) r_inc *= -1;
		r += r_inc;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();		
	}

	glfwTerminate();
	return 0;
}