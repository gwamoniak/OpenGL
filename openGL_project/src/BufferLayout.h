#pragma once

#include "Renderer.h"
#include <vector>

struct BufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static constexpr unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:        return 4;
			case GL_UNSIGNED_INT: return 4;
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout();
	~BufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		//m_Stride += sizeof(GLfloat);
		m_Stride += BufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		//m_Stride += sizeof(GLuint);
		m_Stride += BufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	inline unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<BufferElement>& GetElements() const { return  m_Elements; };

private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride;
};

