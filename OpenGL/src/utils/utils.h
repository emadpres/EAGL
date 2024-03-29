#pragma once
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak()

namespace eagl {
	
	size_t GetOpenGLTypeSize(GLenum type);
}
