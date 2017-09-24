#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include <D3DX10math.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetLookat(float, float, float);

	D3DXVECTOR3 GetPostion();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetLookat();

	void Render();
	D3DXMATRIX GetViewMatrix();

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	D3DXVECTOR3 m_lookat;
	D3DXMATRIX m_viewMatrix;

};

#endif //_CAMERACLASS_H_
