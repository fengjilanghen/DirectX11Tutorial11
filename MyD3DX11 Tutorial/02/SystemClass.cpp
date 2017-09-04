#include "systemclass.h"

SystemClass::SystemClass()
{

}

SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize()
{
	bool result;
	int width, height;
	result = InitializeWindow(width, height);
	if (!result)
	{
		return false;
	}

	m_input = new InputClass;
	if (!m_input)
	{
		return false;
	}
	m_input->Initialize();

	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	m_Graphics->Initialize(width, height, m_hwnd);

	return true;
}

void SystemClass::Shutdown()
{
	if (m_input)
	{
		delete m_input;
		m_input = NULL;
	}


	ShutdownWindow();
}


void SystemClass::Run()
{
	MSG msg;
	bool bDone = false;
	while (!bDone)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			bDone = true;
		}
		else
		{
			bDone = !Frame();
		}	
	}
}

LRESULT SystemClass::MsgHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		m_input->KeyDown(static_cast<unsigned int>(wparam));
		break;
	case WM_KEYUP:
		m_input->KeyUp(static_cast<unsigned int>(wparam));
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

bool SystemClass::Frame()
{
	bool result;
	if (m_input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}
	return true;
}

bool SystemClass::InitializeWindow(int &w, int &h)
{
	ApplicationHandle = this;
	m_hinstance = GetModuleHandle(NULL);
	m_ApplicationName = L"Engine";
	int posX, posY;

	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = HBRUSH(GetStockObject(GRAY_BRUSH));
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = m_ApplicationName;
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hInstance = m_hinstance;
	
	RegisterClassEx(&wc);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	DEVMODE dmScreenSettings;
	if (FULL_SCREEN)
	{
		w = screenWidth;
		h = screenHeight;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		w = 800;
		h = 600;
		posX = (screenWidth - w) / 2;
		posY = (screenHeight - h) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName,
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, 
		posX, posY, w, h, NULL, NULL, m_hinstance, 0);
	if (!m_hwnd)
	{
		return false;
	}
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	ShowCursor(true);

	return true;
}

void SystemClass::ShutdownWindow()
{
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	if (m_hwnd)
	{
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;
	}

	UnregisterClass(m_ApplicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return ApplicationHandle->MsgHandler(hwnd, msg, wparam, lparam);
	}
	}
}

