#ifndef _GRAPHICSCLASS_
#define _GRAPHICSCLASS_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "d3dclass.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_NEAR = 0.1f;
const float SCREEN_DEPTH = 1000.0f;

class GraphicsClass
{
public:
	GraphicsClass();
	~GraphicsClass();

	bool Initialize(int width, int height, HWND hwnd);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3dClass*	m_D3D;
};



#endif //_GRAPHICSCLASS_