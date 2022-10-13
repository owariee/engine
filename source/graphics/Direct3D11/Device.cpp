#include "Device.h"

Device::Device(Window* window)
{
    Device::pDevice = nullptr;
    Device::pSwapChain = nullptr;
    Device::pContext = nullptr;
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = *(window->getHandle());
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &(Device::pSwapChain),
        &(Device::pDevice),
        nullptr,
        &(Device::pContext)
    );

    Device::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

Device::~Device()
{
    Device::pContext->Release();
    Device::pSwapChain->Release();
    Device::pDevice->Release();   
}

ID3D11Device* Device::getDevice()
{
    return Device::pDevice;
}

IDXGISwapChain* Device::getSwapChain()
{
    return Device::pSwapChain;
}

ID3D11DeviceContext* Device::getContext()
{
    return Device::pContext;
}

void Device::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
    Device::pContext->IASetPrimitiveTopology(topology);
}
