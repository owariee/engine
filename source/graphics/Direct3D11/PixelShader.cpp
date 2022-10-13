#include "PixelShader.h"

#include <d3dcompiler.h>

ID3DBlob* PixelShader::shaderBlob = nullptr;

void PixelShader::createShader(LPCWSTR shaderName)
{
    D3DReadFileToBlob(shaderName, &(PixelShader::shaderBlob));
    PixelShader::pPixelShader = nullptr;
    PixelShader::device->getDevice()->CreatePixelShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &(PixelShader::pPixelShader)
    );
}

PixelShader::PixelShader(LPCWSTR shaderName, Device* device) : device(device)
{
    PixelShader::createShader(shaderName);
    PixelShader::use();
}

PixelShader::~PixelShader()
{
    PixelShader::pPixelShader->Release();
}

void PixelShader::use()
{
    PixelShader::device->getContext()->PSSetShader((PixelShader::pPixelShader), nullptr, 0u);
}

ID3DBlob* PixelShader::getBlob()
{
    return (PixelShader::shaderBlob);
}
