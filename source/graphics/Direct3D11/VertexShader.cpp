#include "VertexShader.h"

#include <d3dcompiler.h>

ID3DBlob* VertexShader::shaderBlob = nullptr;

void VertexShader::createShader(LPCWSTR shaderName)
{
    D3DReadFileToBlob(shaderName, &(VertexShader::shaderBlob));
    VertexShader::pVertexShader = nullptr;
    VertexShader::device->getDevice()->CreateVertexShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        nullptr,
        &(VertexShader::pVertexShader)
    );
}

VertexShader::VertexShader(LPCWSTR shaderName, Device* device) : device(device)
{
    VertexShader::createShader(shaderName);
    VertexShader::use();
}

VertexShader::~VertexShader()
{
    VertexShader::pVertexShader->Release();
}

void VertexShader::use()
{
    VertexShader::device->getContext()->VSSetShader((VertexShader::pVertexShader), nullptr, 0u);
}

ID3DBlob* VertexShader::getBlob()
{
    return (VertexShader::shaderBlob);
}
