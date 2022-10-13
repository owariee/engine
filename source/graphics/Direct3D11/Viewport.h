#pragma once

#include "Device.h"

class Viewport
{
private:
	D3D11_VIEWPORT* vp;
	Device* device;

	void createViewport(float width, float height);
public:
	Viewport(float width, float height, Device* device);
	~Viewport();

	void use();
	float getWidth();
	float getHeight();
};
