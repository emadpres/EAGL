#pragma once
#include <vector>

#include "Renderer.h"

namespace eagl{
	class BufferLayout {
		struct Attrib {
			unsigned int m_count;
			unsigned int m_type;
			unsigned int m_offset;
		};

		std::vector<Attrib> m_layouts;
		unsigned int m_stride;
	public:
		BufferLayout():m_stride(0) {}
		~BufferLayout() {}

		void Add(unsigned int count, unsigned int type)
		{
			m_layouts.push_back({ count, type, m_stride});
			m_stride += count * GetOpenGLTypeSize(type);
		}

		const std::vector<Attrib>& GetLayout() const { return m_layouts; }
		unsigned int GetStride() const { return m_stride; }
	};
}