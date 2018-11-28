#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
//#include "BufferLayout.h"

class BufferLayout;


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);
	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
};

