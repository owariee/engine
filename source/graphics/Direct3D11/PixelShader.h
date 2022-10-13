#pragma once

#include "Device.h"

#include <d3d11.h>

class PixelShader
{
private:
	ID3D11PixelShader* pPixelShader;
	Device* device;
	static ID3DBlob* shaderBlob;

	void createShader(LPCWSTR shaderName);
public:
	PixelShader(LPCWSTR shaderName, Device* device);
	~PixelShader();

	void use();
	ID3DBlob* getBlob();
};
