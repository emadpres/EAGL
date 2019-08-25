#pragma once

#include "Renderer.h"

namespace eagl {
	class IndexBuffer {
		unsigned int m_renderedId;
		unsigned int m_count, m_type;
	public:
		IndexBuffer(unsigned int count, unsigned int type, const void* data)
			:m_count(count), m_type(type)
		{
			// 1. Create a (index) buffer
			glGenBuffers(1, &m_renderedId);
			// 2. Bind buffer to GL_ELEMENT_ARRAY_BUFFER ==> for vertex buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderedId);
			// 3. Set the data (for the buffer binded currently to GL_ELEMENT_ARRAY_BUFFER)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * GetOpenGLTypeSize(type), data, GL_STATIC_DRAW);
		}

		~IndexBuffer()
		{
			glDeleteBuffers(1, &m_renderedId);
		}

		void Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderedId);
		}

		void Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		unsigned int GetCount() const
		{
			return m_count;
		}

		unsigned int GetType() const
		{
			return m_type;
		}

	};
}