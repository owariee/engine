// dawn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <string>
#include <sstream>
#include <d3d11.h>

#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexLayout.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "Device.h"
#include "Viewport.h"
#include "RenderTarget.h"
#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const Vertex vertices[] = {
        { 0.0f,  0.5f},
        { 0.5f, -0.5f},
        {-0.5f, -0.5f},
    };

    const D3D11_INPUT_ELEMENT_DESC ied[] = {
        { "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    // Refactor Window Message Loop
    // Change from GetMessage to PeekMessage

    Window window(200, 200, 640, 480, "dawn", "Dawn");
    Device d3dDevice(&window);
    RenderTarget rt(&d3dDevice);
    VertexBuffer vbuffer(vertices, sizeof(vertices), &d3dDevice);
    VertexShader vshader(L"BasicVertex.cso", &d3dDevice);
    PixelShader pshader(L"BasicPixel.cso", &d3dDevice);
    VertexLayout vlayout(ied, (UINT)std::size(ied), vshader.getBlob(), &d3dDevice);
    Viewport vport(640, 480, &d3dDevice);
    
    MSG msg = { 0 };
    BOOL gResult;
    while (gResult = GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        rt.clear();
        d3dDevice.getContext()->Draw((UINT)std::size(vertices), 0u);
        d3dDevice.getSwapChain()->Present(1u, 0u);
    }

    if (gResult == -1)
    {
        return -1;
    }
    else
    {
        return (int)msg.wParam;
    }
}
