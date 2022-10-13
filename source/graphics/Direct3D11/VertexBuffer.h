#pragma once

#include "Device.h"

#include <d3d11.h>

class VertexBuffer
{
private:
	ID3D11Buffer* pVertexBuffer;
	Device* device;

	void createBuffer(const void* vertices, UINT size);
public:
	VertexBuffer(const void* vertices, UINT size, Device* device);
	~VertexBuffer();

	void use();
};
