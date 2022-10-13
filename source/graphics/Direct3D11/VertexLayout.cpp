#include "VertexLayout.h"

void VertexLayout::createLayout(const D3D11_INPUT_ELEMENT_DESC ied[], UINT size, ID3DBlob* shaderBlob)
{
    VertexLayout::device->getDevice()->CreateInputLayout(
        ied,
        size,
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(),
        &(VertexLayout::pInputLayout)
    );
}

VertexLayout::VertexLayout(const D3D11_INPUT_ELEMENT_DESC ied[], UINT size, ID3DBlob* shaderBlob, Device* device) : device(device)
{
    VertexLayout::createLayout(ied, size, shaderBlob);
    VertexLayout::use();
}

VertexLayout::~VertexLayout()
{
    VertexLayout::pInputLayout->Release();
}

void VertexLayout::use()
{
    VertexLayout::device->getContext()->IASetInputLayout((VertexLayout::pInputLayout));
}
