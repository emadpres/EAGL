#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform vec4 u_pos_offset;

void main()
{
	gl_Position =  position+u_pos_offset;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
	color = u_color;
}