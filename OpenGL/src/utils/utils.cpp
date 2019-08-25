#include "utils.h"

namespace eagl {
	
	size_t GetOpenGLTypeSize(GLenum type)
	{
		switch (type)
		{
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return sizeof(char);
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
			return sizeof(short);
		case GL_INT:
		case GL_UNSIGNED_INT:
			return sizeof(int);
		case GL_FLOAT:
			return sizeof(float);
		case GL_DOUBLE:
			return sizeof(double);
		default:
			ASSERT(0);
			return 0;
		}
	}
}
