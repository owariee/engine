#pragma once

#include "Window.h"

#include <d3d11.h>

class Device
{
private:
    ID3D11Device* pDevice;
    IDXGISwapChain* pSwapChain;
    ID3D11DeviceContext* pContext;

public:
    Device(Window* window);
    ~Device();

    ID3D11Device* getDevice();
    IDXGISwapChain* getSwapChain();
    ID3D11DeviceContext* getContext();
    void setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
};
