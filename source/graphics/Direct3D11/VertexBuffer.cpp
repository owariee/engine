#include "VertexBuffer.h"

#include "Vertex.h"

void VertexBuffer::createBuffer(const void* vertices, UINT size)
{
    VertexBuffer::pVertexBuffer = nullptr;
    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = size;
    bd.StructureByteStride = sizeof(Vertex);
    D3D11_SUBRESOURCE_DATA subdata = {};
    subdata.pSysMem = vertices;
    VertexBuffer::device->getDevice()->CreateBuffer(&bd, &subdata, &(VertexBuffer::pVertexBuffer));
}

VertexBuffer::VertexBuffer(const void* vertices, UINT size, Device* device) : device(device)
{
    VertexBuffer::createBuffer(vertices, size);
    VertexBuffer::use();
}

VertexBuffer::~VertexBuffer()
{
    VertexBuffer::pVertexBuffer->Release();
}

void VertexBuffer::use()
{
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;
    VertexBuffer::device->getContext()->IASetVertexBuffers(0u, 1u, &(VertexBuffer::pVertexBuffer), &stride, &offset);
}
