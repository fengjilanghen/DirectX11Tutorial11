#ifndef _INPUTCLASS_
#define _INPUTCLASS_

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();
	void KeyDown(unsigned int keycode);
	void KeyUp(unsigned int keycode);

	bool IsKeyDown(unsigned int keycode);

private:
	bool m_Key[256];
};

#endif // _INPUTCLASS_
