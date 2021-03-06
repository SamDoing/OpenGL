#pragma once
#include "VertexBufferLayout.h"

class VertexBuffer 
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};
