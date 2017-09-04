#include "inputclass.h"

InputClass::InputClass()
{

}


InputClass::InputClass(const InputClass&)
{

}

InputClass::~InputClass()
{

}


void InputClass::Initialize()
{
	for (int i = 0; i < 256; ++i)
	{
		m_Key[i] = false;
	}
}

void InputClass::KeyDown(unsigned int keycode)
{
	m_Key[keycode] = true;
}

void InputClass::KeyUp(unsigned int keycode)
{
	m_Key[keycode] = false;
}

bool InputClass::IsKeyDown(unsigned int keycode)
{
	return m_Key[keycode];
}