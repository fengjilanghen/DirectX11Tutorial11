#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass&)
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool ret;

	ret = InitializeBuffers(device);
	if (!ret)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	ShutdownBuffers();
}

void ModelClass::Render(ID3D11DeviceContext* context)
{
	RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;
	VertexType vertices[3];
	vertices[0] = { D3DXVECTOR3(0, 1, 1), D3DXVECTOR3(1, 0, 0) };
	vertices[1] = { D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, 1, 0) };
	vertices[2] = { D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, 0, 1) };

	unsigned int indices[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	D3D11_BUFFER_DESC vertexBuffer, indexBuffer;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBuffer.ByteWidth = sizeof(vertices);
	vertexBuffer.CPUAccessFlags = 0;
	vertexBuffer.MiscFlags = 0;
	vertexBuffer.StructureByteStride = 0;
	vertexBuffer.Usage = D3D11_USAGE_DEFAULT;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBuffer, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBuffer.Usage = D3D11_USAGE_DEFAULT;
	indexBuffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
	vertexBuffer.ByteWidth = sizeof(indices);
	indexBuffer.CPUAccessFlags = 0;
	vertexBuffer.MiscFlags = 0;
	vertexBuffer.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	result = device->CreateBuffer(&indexBuffer, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ModelClass::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(VertexType), offset = 0;
	context->IASetVertexBuffers(0, 1, &m_vertexBuffer,&stride, &offset );
	context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

