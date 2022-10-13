#include "Viewport.h"

void Viewport::createViewport(float width, float height)
{
    Viewport::vp = new D3D11_VIEWPORT;
    Viewport::vp->Width = width;
    Viewport::vp->Height = height;
    Viewport::vp->MinDepth = 0;
    Viewport::vp->MaxDepth = 1;
    Viewport::vp->TopLeftX = 0;
    Viewport::vp->TopLeftY = 0;
}

Viewport::Viewport(float width, float height, Device* device) : device(device)
{
    Viewport::createViewport(width, height);
    Viewport::use();
}

Viewport::~Viewport()
{
    delete (Viewport::vp);
}

void Viewport::use()
{
    Viewport::device->getContext()->RSSetViewports(1, (Viewport::vp));
}

float Viewport::getWidth()
{
    return vp->Width;
}

float Viewport::getHeight()
{
    return vp->Height;
}
