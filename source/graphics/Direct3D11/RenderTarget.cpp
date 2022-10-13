#include "RenderTarget.h"


void RenderTarget::createRenderTarget()
{
    RenderTarget::pTarget = nullptr;
    ID3D11Resource* pBackBuffer = nullptr;
    RenderTarget::device->getSwapChain()->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
    RenderTarget::device->getDevice()->CreateRenderTargetView(pBackBuffer, nullptr, &(RenderTarget::pTarget));
    pBackBuffer->Release();
}

RenderTarget::RenderTarget(Device* device) : device(device)
{
    RenderTarget::createRenderTarget();
    RenderTarget::setClearColor(0.0f, 0.0f, 0.0f);
    RenderTarget::clear();
    RenderTarget::use();
}

RenderTarget::~RenderTarget()
{
    RenderTarget::pTarget->Release();
}

void RenderTarget::use()
{
    RenderTarget::device->getContext()->OMSetRenderTargets(1, &pTarget, nullptr);
}

void RenderTarget::clear()
{
    const float color[] = { RenderTarget::clearR, RenderTarget::clearG, RenderTarget::clearB, 1.0f };
    RenderTarget::device->getContext()->ClearRenderTargetView(pTarget, color);
}

void RenderTarget::setClearColor(float r, float g, float b)
{
    RenderTarget::clearR = r;
    RenderTarget::clearG = g;
    RenderTarget::clearB = b;
}

ID3D11RenderTargetView* RenderTarget::getRenderTarget()
{
    return RenderTarget::pTarget;
}
