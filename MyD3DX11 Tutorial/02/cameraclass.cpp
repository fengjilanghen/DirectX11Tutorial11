#include "cameraclass.h"

CameraClass::CameraClass()
{

}

CameraClass::CameraClass(const CameraClass&)
{

}

CameraClass::CameraClass()
{

}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position = D3DXVECTOR3(x, y, z);
}


void CameraClass::SetLookat(float x, float y, float z)
{
	m_lookat = D3DXVECTOR3(x, y, z);
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR3 CameraClass::GetPostion()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return m_rotation;
}

D3DXVECTOR3 CameraClass::GetLookat()
{
	return m_lookat;
}

void CameraClass::Render()
{
	D3DXVECTOR3 zaxis = m_lookat - m_position;
	D3DXVECTOR3 up = D3DXVECTOR3(0, 0, 1);

	D3DXMATRIX rotationMatrix;
	D3DXVECTOR3 rotation = m_rotation * 0.174532925f;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rotation.x, rotation.y, rotation.z);

	D3DXVec3TransformCoord(&zaxis, &zaxis, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	D3DXVECTOR3 lookat = m_position + zaxis;
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &lookat, &up);
}

D3DXMATRIX CameraClass::GetViewMatrix()
{
	return m_viewMatrix;
}