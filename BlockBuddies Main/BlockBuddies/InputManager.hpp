#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

class InputManager
{
public:
	static InputManager* getInstance();
	void init();
	void update();
	bool mouseReleased;
	
private:
	InputManager(){};
	InputManager(InputManager const&){};
	InputManager& operator=(InputManager const&){};

	static InputManager* instance;
};

#endif//INPUTMANAGER_HPP