#pragma once

#include "Device.h"

class VertexLayout
{
private:
	ID3D11InputLayout* pInputLayout;
	Device* device;

	void createLayout(const D3D11_INPUT_ELEMENT_DESC ied[], UINT size, ID3DBlob* shaderBlob);
public:
	VertexLayout(const D3D11_INPUT_ELEMENT_DESC ied[], UINT size, ID3DBlob* shaderBlob, Device* device);
	~VertexLayout();

	void use();
};
