#pragma once

#include "Renderer.h"

namespace eagl {
	class VertexBuffer {
		unsigned int m_renderedId;
	public:
		VertexBuffer(unsigned int size, const void* data)
		{
			// 1. Create a (vertex/data) buffer
			glGenBuffers(1, &m_renderedId);
			// 2. Bind buffer to GL_ARRAY_BUFFER ==> for vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_renderedId);
			// 3. (while binded) Set the data (for the buffer binded currently to GL_ARRAY_BUFFER)
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		~VertexBuffer()
		{
			glDeleteBuffers(1, &m_renderedId);
		}

		void Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_renderedId);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	};
}