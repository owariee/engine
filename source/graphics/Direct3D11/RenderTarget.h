#pragma once

#include "Device.h"

class RenderTarget
{
private:
	ID3D11RenderTargetView* pTarget;
	float clearR;
	float clearG;
	float clearB;
	Device* device;

	void createRenderTarget();
public:
	RenderTarget(Device* device);
	~RenderTarget();

	void use();
	void clear();
	void setClearColor(float r, float g, float b);
	ID3D11RenderTargetView* getRenderTarget();
};
