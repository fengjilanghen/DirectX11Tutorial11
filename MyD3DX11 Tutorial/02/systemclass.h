#ifndef _SYSTEMCLASS_
#define _SYSTEMCLASS_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "graphicsclass.h"
#include "inputclass.h"

class SystemClass
{
public:
	SystemClass();
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MsgHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	bool Frame();
	bool InitializeWindow(int &w, int &h);
	void ShutdownWindow();

private:
	LPCWSTR m_ApplicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass *m_input;
	GraphicsClass *m_Graphics;
};




static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

static SystemClass *ApplicationHandle = 0;

#endif // _SYSTEMCLASS_