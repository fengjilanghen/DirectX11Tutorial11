#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{

}

GraphicsClass::~GraphicsClass()
{

}


bool GraphicsClass::Initialize(int width, int height, HWND hwnd)
{
	bool result;

	m_D3D = new D3dClass;
	if (!m_D3D)
	{
		return false;
	}
	result = m_D3D->Initialize(width, height, VSYNC_ENABLED, hwnd, false, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{

}

bool GraphicsClass::Frame()
{
	bool result;
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	return true;
}
