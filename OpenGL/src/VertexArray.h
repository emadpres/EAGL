#pragma once

#include "Renderer.h"
#include "BufferLayout.h"
#include "VertextBuffer.h"

namespace eagl {
	class VertexArray {
		unsigned int m_rendererId;
	public:
		VertexArray(const VertexBuffer* vb, const BufferLayout& layout, const IndexBuffer* ib)
		{
			glGenVertexArrays(1, &m_rendererId);
			Bind();

			vb->Bind();
			const auto attributes = layout.GetLayout();
			for (int i = 0; i < attributes.size(); i++)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, attributes[i].m_count, attributes[i].m_type, GL_FALSE, layout.GetStride(), (void*)attributes[i].m_offset);
			}
			
			if(ib)
				ib->Bind();
			Unbind();

			vb->Unbind();
			if(ib)
				ib->Unbind();
		}

		void Bind() const {
			glBindVertexArray(m_rendererId);
		}

		void Unbind() const
		{
			glBindVertexArray(0);
		}
	};
}