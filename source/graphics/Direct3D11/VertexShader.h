#pragma once

#include "Device.h"

class VertexShader
{
private:
	ID3D11VertexShader* pVertexShader;
	Device* device;
	static ID3DBlob* shaderBlob;

	void createShader(LPCWSTR shaderName);
public:
	VertexShader(LPCWSTR shaderName, Device* device);
	~VertexShader();

	void use();
	ID3DBlob* getBlob();
};
